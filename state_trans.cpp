/*
 struct WindowsPort {
	int State;
	int CurNum, CurCustTime;
	int CurStateTime;
	int TotOffTime, TotOnTime;
	int TotServeTime, TotNum, ScheRestTime, RestSignal, TotRestTime;
 };
*/

#include <ctime>
#include "Definition.h"
using namespace std;

void state_trans(string CurTimeRequestOfWindows) {
	int i;
	for (i = 1; i <= MAX_WINDOWS; i++) {
		switch (windows[i].State) {
		case AVAILABLE_PORT://空闲状态
			windows[i].CurStateTime = 0;
			if (windows[i].CurNum > 0) {
				windows[i].CurStateTime = 1;
				srand((unsigned)time(0));
				srand(rand());
				windows[i].CurCustTime = rand() % (MaxTimeLen - MinTimeLen) + MinTimeLen;
				windows[i].State = 2;
			}
			windows[i].TotOnTime++;
			break;
		case CHECKING_PORT://正在安检
			windows[i].CurStateTime++;
			if (windows[i].CurStateTime == windows[i].CurCustTime) {
				windows[i].State = 3;
				windows[i].CurNum--;
				windows[i].TotNum++;
				windows[i].TotServeTime += windows[i].CurCustTime;
			}
			windows[i].TotOnTime++;
			break;
		case SWITCHING_PORT://此人安检结束，或休息刚结束。状态转换
			windows[i].CurStateTime = 1;
			if (windows[i].CurNum > 0) {//若还有人在排队，则安排下一个人安检
				srand(rand());
				windows[i].CurCustTime = rand() % (MaxTimeLen - MinTimeLen + 1) + MinTimeLen;
				windows[i].State = 2;
				windows[i].TotOnTime++;
			}
			else if (windows[i].CurNum == 0) {//若没有人排队
				if (windows[i].RestSignal == 0) {//若无休息许可，进入空闲状态（1）
					windows[i].State = 1;
					windows[i].TotOnTime++;
				}
				else {//若有休息许可，进入休息状态（4）
					windows[i].State = 4;
					srand((unsigned)time(0));
					srand(rand());
					windows[i].ScheRestTime = rand() % (MaxRestSec - MinRestSec + 1) + MinRestSec;
					windows[i].CurCustTime = 0;
					//                        windows[i].TotRestTime = 1;
				}
			}
			break;
		case RESTTING_PORT://休息
			if (CurTimeRequestOfWindows[i] == '0') {
				windows[i].CurStateTime++;
				if (windows[i].CurStateTime == windows[i].ScheRestTime) {
					windows[i].TotOffTime += windows[i].ScheRestTime;
					windows[i].State = 3;
					windows[i].TotOnTime++;
				}
			}
			else if (CurTimeRequestOfWindows[i] == '1') {
				windows[i].TotOffTime += windows[i].ScheRestTime;
				windows[i].State = 1;
				windows[i].TotOnTime++;
			}
			//                windows[i].TotRestTime ++;
			windows[i].RestSignal = 0;
			break;
		case CLOSE_PORT://关闭
			break;
		}
	}
}
