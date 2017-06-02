#include <cmath>
#include <fstream>
#include "Definition.h"

using namespace std;

static struct WindowsPort s_windowsBU[MAX_WINDOWS] = { 0 };

int is_equal();

extern int g_AveWaitTime, g_Time;

void output_via_file(const int QueueNum, const int State) {
	//定义两个输出流
	static ofstream fout("output.log", ofstream::out);
	static ofstream foutD("outputDetail.log", ofstream::out);
	if (foutD) {
		//输出时间，上下班状态
		foutD << "Time is " << g_Time << endl;
		foutD << "OFFDUTY=";
		if (State == 1) {
			foutD << "N" << endl;
		}
		else {
			foutD << "Y" << endl;
		}
		//输出抬头
		foutD << "No.	State	CurNum	CurCustTime	WinListCustCount	Tot	ScheRestTime	TotOffTime" << endl;
		//输出详细数据
		for (int i = 1; i <= REAL_WINDOWS; ++i) {
			foutD << i << "	" << g_windows[i].State;
			foutD << "	" << g_windows[i].CurNum
				<< "		" << g_windows[i].CurCustTime
				<< "		" << g_windows[i].CurNum
				<< "		" << g_windows[i].TotNum
				<< "	" << g_windows[i].ScheRestTime
				<< "		" << g_windows[i].TotOffTime;
			foutD << endl;
		}
		//输出蛇形队列个数，等待人数，期望等待时间
		if (QueueNum == g_MaxCustSingleLine * g_MaxLines) {
			foutD << "Out of Queue" << endl;
		}
		foutD << "ListLines = " << (ceil((double)QueueNum / g_MaxCustSingleLine) != 0 ? ceil((double)QueueNum / g_MaxCustSingleLine) : 1) << endl;
		foutD << "ListCustCount = " << QueueNum << endl;
		foutD << "Average Waiting g_Time = " << g_AveWaitTime << endl << endl;
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
			fout << "Time is " << g_Time << endl;
			fout << "OFFDUTY=";
			if (State == 0) {
				fout << "Y" << endl;
			}
			else {
				fout << "N" << endl;
			}
			//输出抬头
			fout << "No.	State	CurNum	CurCustTime	WinListCustCount	Tot	ScheRestTime	TotOffTime" << endl;
			//输出详细数据
			for (int i = 1; i <= REAL_WINDOWS; ++i) {
				fout << i << "	" << g_windows[i].State;
				fout << "	" << g_windows[i].CurNum
					<< "		" << g_windows[i].CurCustTime
					<< "		" << g_windows[i].CurNum
					<< "		" << g_windows[i].TotNum
					<< "	" << g_windows[i].ScheRestTime
					<< "		" << g_windows[i].TotOffTime;
				fout << endl;
			}
			//输出蛇形队列个数，等待人数，期望等待时间
			if (QueueNum == g_MaxCustSingleLine * g_MaxLines) {
				fout << "Out of Queue" << endl;
			}
			fout << "ListLines = " << (ceil((double)QueueNum / g_MaxCustSingleLine) != 0 ? ceil((double)QueueNum / g_MaxCustSingleLine) : 1) << endl;
			fout << "ListCustCount = " << QueueNum << endl;
			fout << "Average Waiting g_Time = " << g_AveWaitTime << endl << endl;
		}
	}
	else {
		//fail echo
		cout << "Can't record the Output Log" << endl;
	}
}

void output_via_keyboard(const int QueueNum, const int State) {
	//输出时间，上下班状态
	cout << "Time is " << g_Time << endl;
	cout << "OFFDUTY=";
	if (State == 0) {
		cout << "Y" << endl;
	}
	else {
		cout << "N" << endl;
	}
	//输出抬头
	cout << "No.	State	CurNum	CurCustTime	WinListCustCount	Tot	ScheRestTime	TotOffTime" << endl;
	//输出详细数据
	for (int i = 1; i <= REAL_WINDOWS; ++i) {
		cout << i << "	" << g_windows[i].State;
		cout << "	" << g_windows[i].CurNum
			<< "		" << g_windows[i].CurCustTime
			<< "		" << g_windows[i].CurNum
			<< "		" << g_windows[i].TotNum
			<< "	" << g_windows[i].ScheRestTime
			<< "		" << g_windows[i].TotOffTime;
		cout << endl;
	}
	//输出蛇形队列个数，等待人数，期望等待时间
	if (QueueNum == g_MaxCustSingleLine * g_MaxLines) {
		cout << "Out of Queue" << endl;
	}
	cout << "ListLines = " << (ceil((double)QueueNum / g_MaxCustSingleLine) != 0 ? ceil((double)QueueNum / g_MaxCustSingleLine) : 1) << endl;
	cout << "ListCustCount = " << QueueNum << endl;
	cout << "Average Waiting g_Time = " << g_AveWaitTime << endl << endl;
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