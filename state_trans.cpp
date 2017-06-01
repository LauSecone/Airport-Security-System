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
static default_random_engine e(time(NULL));

void state_trans(const string &CurTimeRequestOfWindows) {
	int i;
	for (i = 1; i <= MAX_WINDOWS; ++i) {
		if (windows[i].RestSignal == 1 && windows[i].State == 1) {
			windows[i].RestSignal = 0;
			windows[i].State = RESTTING_PORT;
			windows[i].CurStateTime = 1;
			static uniform_int_distribution<unsigned> u(MinRestSec, MaxRestSec);
			windows[i].ScheRestTime = u(e);
			return;
		}
		switch (windows[i].State) {
		case AVAILABLE_PORT://空闲状态
			windows[i].CurStateTime = 0;
			if (windows[i].CurNum > 0) {
				windows[i].CurStateTime = 1;
				static uniform_int_distribution<unsigned> u(MinTimeLen, MaxTimeLen);
				windows[i].CurCustTime = u(e);
				windows[i].State = AVAILABLE_PORT;
			}
			windows[i].TotOnTime++;
			break;
		case CHECKING_PORT://正在安检
			++windows[i].CurStateTime;
			if (windows[i].CurStateTime == windows[i].CurCustTime) {
				windows[i].State = SWITCHING_PORT;
				--windows[i].CurNum;
				++windows[i].TotNum;
				windows[i].TotServeTime += windows[i].CurCustTime;
				windows[i].CurCustTime = 0;
			}
			++windows[i].TotOnTime;
			break;
		case SWITCHING_PORT://此人安检结束，或休息刚结束。状态转换
			windows[i].CurStateTime = 1;
			if (windows[i].CurNum > 0) {//若还有人在排队，则安排下一个人安检
				srand(rand());
				static uniform_int_distribution<unsigned> u(MinTimeLen, MaxTimeLen);
				windows[i].CurCustTime = u(e);
				windows[i].State = AVAILABLE_PORT;
				windows[i].TotOnTime++;
			}
			else if (windows[i].CurNum == 0) {//若没有人排队
				windows[i].State = AVAILABLE_PORT;
				++windows[i].TotOnTime;
			}
			break;
		case RESTTING_PORT://休息
			if (CurTimeRequestOfWindows[i] == '0') {//若未申请恢复
				++windows[i].CurStateTime;
				if (windows[i].CurStateTime == windows[i].ScheRestTime) {
					windows[i].TotOffTime += windows[i].ScheRestTime;
					windows[i].ScheRestTime = 0;
					windows[i].State = SWITCHING_PORT;
					++windows[i].TotOnTime;
				}
			}
			else if (CurTimeRequestOfWindows[i] == 'C') {//若申请恢复
				windows[i].TotOffTime += windows[i].ScheRestTime;
				windows[i].ScheRestTime = 0;
				windows[i].State = AVAILABLE_PORT;
				++windows[i].TotOnTime;
			}
			break;
		case CLOSE_PORT://关闭
			break;
		}
	}
}
