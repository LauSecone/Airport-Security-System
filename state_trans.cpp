/*
	struct WindowsPort {
	int State;	//the state of windows
	int CurNum; //current guest number of windows
	int CurStateTime;
	int CurGuestTime;
	int TotOffTime, TotOnTime, TotServeTime, TotNum, ScheRestTime;
	int RestSignal;
}

MaxCustSingleLine（单队列最大等待乘客数），MaxLines（蛇形缓冲区最多由MaxLines个直队组成）、MaxSeqLen（最大允许等待长度）、MinTimeLen（一次安检最短时长，单位为分钟），MaxTimeLen（一次安检最长时长，单位为分钟）
}
*/

#include <ctime>
#include "Definition.h"
using namespace std;

void state_trans(string CurTimeRequestOfWindows) {
	int i;
	for (i = 1; i <= MAX_WINDOWS; i++) {
		switch (windows[i].State) {
		case 1://空闲状态
			if (windows[i].CurNum > 0) {
				windows[i].CurStateTime = 1;
				windows[i].CurNum--;
				windows[i].TotNum++;
				srand((unsigned)time(0));
				windows[i].CurCustTime = rand() % (MaxTimeLen - MinTimeLen) + MinTimeLen;
				windows[i].State = 2;
			}
			windows[i].TotOnTime++;
			break;
		case 2://正在安检
			windows[i].CurStateTime++;
			if (windows[i].CurStateTime == windows[i].CurCustTime - 1)
				windows[i].State = 3;
			windows[i].TotOnTime++;
			break;
		case 3://此人安检结束，下一个人开始安检
			windows[i].CurStateTime = 1;
			windows[i].TotServeTime += windows[i].CurCustTime;
			if (windows[i].CurNum > 0) {//若还有人在排队，则安排下一个人安检
				windows[i].CurNum--;
				windows[i].TotNum++;
				srand((unsigned)time(0));
				windows[i].CurCustTime = rand() % (MaxTimeLen - MinTimeLen) + MinTimeLen;
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
				}
			}
			break;
		case 4://休息
			if (CurTimeRequestOfWindows[i] == 0) {
				windows[i].CurStateTime++;
				if (windows[i].CurStateTime == windows[i].ScheRestTime) {
					windows[i].TotOffTime += windows[i].ScheRestTime;
					windows[i].State = 1;
					windows[i].TotOnTime++;
				}
			}
			else if (CurTimeRequestOfWindows[i] == 1) {
				windows[i].TotOffTime += windows[i].ScheRestTime;
				windows[i].State = 1;
				windows[i].TotOnTime++;
			}
			windows[i].RestSignal = 0;
			break;
		case 5://关闭
			break;
		}
	}
}
