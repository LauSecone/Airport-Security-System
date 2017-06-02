#include "Definition.h"
using namespace std;

struct WindowsPort g_windows[MAX_WINDOWS] = { 0 };
int g_MaxCustSingleLine, g_MaxLines, g_MaxSeqLen, g_MinTimeLen, g_MaxTimeLen, g_MinRestSec, g_MaxRestSec;
int g_AveWaitTime = 0;

void init(int &, int &);
void input_via_file(int &, string &, int &);
void input_via_keyboard(int &, string &, int &);
void output_via_file(int, int);
void output_via_keyboard(int, int);
void check_quit(int &);
void state_trans(const string &);
void rest_or_not(int &, const string &);
void allo_cust(int &);
void come_in_cust(int &, int);

int g_Time = 0;

int main() {
	//初始化
	int State = ON_DUTY, QueueNum = 0, in = 0, out = 0;
	init(in, out);
	while (State) {
		++g_Time;
		//用于保存当前时刻的输入数据
		string CurTimeRequestOfWindows(MAX_WINDOWS, '0');
		int CurTimeNumOfCustCome = 0;

		//input();
		if (in) {
			input_via_keyboard(CurTimeNumOfCustCome, CurTimeRequestOfWindows, State);
		}
		else {
			input_via_file(CurTimeNumOfCustCome, CurTimeRequestOfWindows, State);
		}
		//process();
		rest_or_not(QueueNum, CurTimeRequestOfWindows);
		allo_cust(QueueNum);
		come_in_cust(QueueNum, CurTimeNumOfCustCome);
		state_trans(CurTimeRequestOfWindows);
		check_quit(State);
		//output();
		if (out) {
			output_via_keyboard(QueueNum, State);
		}
		else {
			output_via_file(QueueNum, State);
		}
	}
	//echo
	cout << "Completed, please check the program log" << endl;
	system("pause");
	return 0;
}
