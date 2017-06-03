/*
 struct WindowsPort {
	int State;
	int CurNum, CurCustTime;
	int CurStateTime;
	int TotOffTime, TotOnTime;
	int TotServeTime, TotNum, ScheRestTime, RestSignal, TotRestTime;
 };
*/

#include <random>
#include <ctime>
#include "Definition.h"

using namespace std;

static default_random_engine e((unsigned int)time(NULL));

void state_trans(const string &CurTimeRequestOfWindows) {
	int i;
	for (i = 1; i <= REAL_WINDOWS; ++i) {
		if (g_windows[i].RestSignal == 1 && g_windows[i].State == 1) {
			g_windows[i].RestSignal = 0;
			g_windows[i].State = RESTTING_PORT;
			g_windows[i].CurStateTime = 1;
			static uniform_int_distribution<unsigned> u(g_MinRestSec, g_MaxRestSec);
			g_windows[i].ScheRestTime = u(e);
			return;
		}
		switch (g_windows[i].State) {
		case AVAILABLE_PORT://空闲状态
			g_windows[i].CurStateTime = 0;
			if (g_windows[i].CurNum > 0) {
				g_windows[i].CurStateTime = 1;
				static uniform_int_distribution<unsigned> u(g_MinTimeLen, g_MaxTimeLen);
				g_windows[i].CurCustTime = u(e);
				g_windows[i].State = CHECKING_PORT;
			}
			g_windows[i].TotOnTime++;
			break;
		case CHECKING_PORT://正在安检
			++g_windows[i].CurStateTime;
			if (g_windows[i].CurStateTime == g_windows[i].CurCustTime) {
				g_windows[i].State = SWITCHING_PORT;
				--g_windows[i].CurNum;
				++g_windows[i].TotNum;
				g_windows[i].TotServeTime += g_windows[i].CurCustTime;
				g_windows[i].CurCustTime = 0;
			}
			++g_windows[i].TotOnTime;
			break;
		case SWITCHING_PORT://此人安检结束，或休息刚结束。状态转换
			g_windows[i].CurStateTime = 1;
			if (g_windows[i].CurNum > 0) {//若还有人在排队，则安排下一个人安检
				static uniform_int_distribution<unsigned> u(g_MinTimeLen, g_MaxTimeLen);
				g_windows[i].CurCustTime = u(e);
				g_windows[i].State = CHECKING_PORT;
				g_windows[i].TotOnTime++;
			}
			else if (g_windows[i].CurNum == 0) {//若没有人排队
				g_windows[i].State = AVAILABLE_PORT;
				++g_windows[i].TotOnTime;
			}
			break;
		case RESTTING_PORT://休息
			if (CurTimeRequestOfWindows[i] == '0') {//若未申请恢复
				++g_windows[i].CurStateTime;
				if (g_windows[i].CurStateTime == g_windows[i].ScheRestTime) {
					g_windows[i].TotOffTime += g_windows[i].ScheRestTime;
					g_windows[i].ScheRestTime = 0;
					g_windows[i].State = SWITCHING_PORT;
					++g_windows[i].TotOnTime;
				}
			}
			else if (CurTimeRequestOfWindows[i] == 'C') {//若申请恢复
				g_windows[i].TotOffTime += g_windows[i].ScheRestTime;
				g_windows[i].ScheRestTime = 0;
				g_windows[i].State = AVAILABLE_PORT;
				++g_windows[i].TotOnTime;
			}
			break;
		case CLOSE_PORT://关闭
			break;
		}
	}
}
