#include "Definition.h"
#include "graphics.h"
#include "PosiDef.h"
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

static struct WindowsPort s_windowsBU[MAX_WINDOWS] = { 0 };
extern int g_AveWaitTime, g_Time;


int is_equal();
void reflesh_panel(int);
void block_button(int);


void output(const int QueueNum, const int State, int out) {
	if (out == WRITE_VIA_FILE) {
		//定义两个输出流
		static ofstream fout("output.log", ofstream::out);
		static ofstream foutD("outputDetail.log", ofstream::out);
		if (foutD) {
			//输出时间，上下班状态
			foutD << "Time is " << g_Time;
			foutD << "	OFFDUTY=";
			if (State == 1) {
				foutD << "N";
			}
			else {
				foutD << "Y";
			}
			foutD << endl;
			//输出抬头
			foutD << "No.	State		CurNum	CurCustTime	Tot	ScheRestTime	TotOffTime	RestSingal" << endl;
			//输出详细数据
			for (int i = 1; i <= REAL_WINDOWS; ++i) {
				foutD << i << "	";
				switch (g_windows[i].State) {
				case 1: foutD << "AVAILABLE"; break;
				case 2: foutD << "CHECKING "; break;
				case 3: foutD << "SWITCHING"; break;
				case 4: foutD << "RESTTING "; break;
				case 5: foutD << "CLOSE    "; break;
				}
				foutD << "	" << g_windows[i].CurNum
					<< "	" << g_windows[i].CurCustTime
					<< "		" << g_windows[i].TotNum
					<< "	" << g_windows[i].ScheRestTime
					<< "		" << g_windows[i].TotOffTime
					<< "		" << g_windows[i].RestSignal;
				foutD << endl;
			}
			//输出蛇形队列个数，等待人数，期望等待时间
			foutD << "ListLines = " << (ceil((double)QueueNum / g_MaxCustSingleLine) != 0 ? ceil((double)QueueNum / g_MaxCustSingleLine) : 1) << endl;
			foutD << "ListCustCount = " << QueueNum;
			if (QueueNum == g_MaxCustSingleLine * g_MaxLines) {
				foutD << "	Out of Queue";
			}
			foutD << endl;
			foutD << "Average Waiting Time = " << g_AveWaitTime << endl << endl;
		}
		else {
			//fail echo
			cout << "Can't record the Output Detail Log." << endl;
		}
		if (fout) {
			if (!is_equal()) {
				//更新状态
				for (int i = 0; i < MAX_WINDOWS; ++i) {
					s_windowsBU[i] = g_windows[i];
				}
				//输出时间，上下班状态
				fout << "Time is " << g_Time;
				fout << "	OFFDUTY=";
				if (State == 1) {
					fout << "N";
				}
				else {
					fout << "Y";
				}
				fout << endl;
				//输出抬头
				fout << "No.	State		CurNum	CurCustTime	Tot	ScheRestTime	TotOffTime	RestSingal" << endl;
				//输出详细数据
				for (int i = 1; i <= REAL_WINDOWS; ++i) {
					fout << i << "	";
					switch (g_windows[i].State) {
					case 1: fout << "AVAILABLE"; break;
					case 2: fout << "CHECKING "; break;
					case 3: fout << "SWITCHING"; break;
					case 4: fout << "RESTTING "; break;
					case 5: fout << "CLOSE    "; break;
					}
					fout << "	" << g_windows[i].CurNum
						<< "	" << g_windows[i].CurCustTime
						<< "		" << g_windows[i].TotNum
						<< "	" << g_windows[i].ScheRestTime
						<< "		" << g_windows[i].TotOffTime
						<< "		" << g_windows[i].RestSignal;
					fout << endl;
				}
				//输出蛇形队列个数，等待人数，期望等待时间
				fout << "ListLines = " << (ceil((double)QueueNum / g_MaxCustSingleLine) != 0 ? ceil((double)QueueNum / g_MaxCustSingleLine) : 1) << endl;
				fout << "ListCustCount = " << QueueNum;
				if (QueueNum == g_MaxCustSingleLine * g_MaxLines) {
					fout << "	Out of Queue";
				}
				fout << endl;
				fout << "Average Waiting Time = " << g_AveWaitTime << endl << endl;
			}
		}
		else {
			//fail echo
			cout << "Can't record the Output Log" << endl;
		}
	}
	if (out == WRITE_VIA_MONITOR) {
		//输出时间，上下班状态
		cout << "Time is " << g_Time;
		cout << "	OFFDUTY=";
		if (State == 1) {
			cout << "N";
		}
		else {
			cout << "Y";
		}
		cout << endl;
		//输出抬头
		cout << "No.	State		CurNum	CurCustTime	Tot	ScheRestTime	TotOffTime	RestSingal" << endl;
		//输出详细数据
		for (int i = 1; i <= REAL_WINDOWS; ++i) {
			cout << i << "	";
			switch (g_windows[i].State) {
			case 1: cout << "AVAILABLE"; break;
			case 2: cout << "CHECKING "; break;
			case 3: cout << "SWITCHING"; break;
			case 4: cout << "RESTTING "; break;
			case 5: cout << "CLOSE    "; break;
			}
			cout << "	" << g_windows[i].CurNum
				<< "	" << g_windows[i].CurCustTime
				<< "		" << g_windows[i].TotNum
				<< "	" << g_windows[i].ScheRestTime
				<< "		" << g_windows[i].TotOffTime
				<< "		" << g_windows[i].RestSignal;
			cout << endl;
		}
		//输出蛇形队列个数，等待人数，期望等待时间
		cout << "ListLines = " << (ceil((double)QueueNum / g_MaxCustSingleLine) != 0 ? ceil((double)QueueNum / g_MaxCustSingleLine) : 1) << endl;
		cout << "ListCustCount = " << QueueNum;
		if (QueueNum == g_MaxCustSingleLine * g_MaxLines) {
			cout << "	Out of Queue";
		}
		cout << endl;
		cout << "Average Waiting Time = " << g_AveWaitTime << endl << endl;
	}
}

int is_equal() {
	for (int i = 0; i < MAX_WINDOWS; ++i) {
		//若出现不同，返回0
		if (s_windowsBU[i].CurNum != g_windows[i].CurNum || s_windowsBU[i].State != g_windows[i].State) {
			return 0;
		}
	}
	return 1;
}

void output_graph(int QueueNum, int State) {
	reflesh_panel(State);

	return;
}

void reflesh_panel(int state) {
	cleardevice();
	PIMAGE img = newimage();
	getimage(img, "run.png");
	putimage(0, 0, img);
	delimage(img);
	block_button(state);
	return;
}

void block_button(int state) {
	if (state == WAIT_FOR_QUIT) {
		imagefilter_blurring(NULL, 0x00, 0x50, Q_X, Q_Y, EBX, EBY);
	}
	for (int i = 0; i < REAL_WINDOWS; ++i) {
		if (g_windows[i + 1].State == CLOSE_PORT || g_windows[i + 1].RestSignal == 1) {
			imagefilter_blurring(NULL, 0x00, 0x50, W_X, W_Y + WD_Y * i, W_X + WX, W_Y + WD_Y * i + WY);
		}
	}
	return;
}