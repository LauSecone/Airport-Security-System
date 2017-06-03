#include <cmath>
#include <fstream>
#include "Definition.h"

using namespace std;

static struct WindowsPort s_windowsBU[MAX_WINDOWS] = { 0 };

int is_equal();

extern int g_AveWaitTime, g_Time;

void output(const int QueueNum, const int State, int out) {
	if (out == WRITE_VIA_FILE) {
		//�������������
		static ofstream fout("output.log", ofstream::out);
		static ofstream foutD("outputDetail.log", ofstream::out);
		if (foutD) {
			//���ʱ�䣬���°�״̬
			foutD << "Time is " << g_Time;
			foutD << "	OFFDUTY=";
			if (State == 1) {
				foutD << "N";
			}
			else {
				foutD << "Y";
			}
			foutD << endl;
			//���̧ͷ
			foutD << "No.	State	CurNum	CurCustTime	WinListCustCount	Tot	ScheRestTime	TotOffTime" << endl;
			//�����ϸ����
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
			//������ζ��и������ȴ������������ȴ�ʱ��
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
				//����״̬
				for (int i = 0; i < MAX_WINDOWS; ++i) {
					s_windowsBU[i] = g_windows[i];
				}
				//���ʱ�䣬���°�״̬
				fout << "Time is " << g_Time;
				fout << "	OFFDUTY=";
				if (State == 0) {
					fout << "Y";
				}
				else {
					fout << "N";
				}
				fout << endl;
				//���̧ͷ
				fout << "No.	State	CurNum	CurCustTime	WinListCustCount	Tot	ScheRestTime	TotOffTime" << endl;
				//�����ϸ����
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
				//������ζ��и������ȴ������������ȴ�ʱ��
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
	if (out == WRITE_VIA_KEYBOARD) {
		//���ʱ�䣬���°�״̬
		cout << "Time is " << g_Time;
		cout << "	OFFDUTY=";
		if (State == 0) {
			cout << "Y";
		}
		else {
			cout << "N";
		}
		cout << endl;
		//���̧ͷ
		cout << "No.	State	CurNum	CurCustTime	WinListCustCount	Tot	ScheRestTime	TotOffTime" << endl;
		//�����ϸ����
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
		//������ζ��и������ȴ������������ȴ�ʱ��
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
		//�����ֲ�ͬ������0
		if (s_windowsBU[i].CurNum != g_windows[i].CurNum || s_windowsBU[i].State != g_windows[i].State) {
			return 0;
		}
	}
	return 1;
}