#include "Definition.h"
using namespace std;

struct WindowsPort g_windows[MAX_WINDOWS] = { 0 };
int g_MaxCustSingleLine, g_MaxLines, g_MaxSeqLen, g_MinTimeLen, g_MaxTimeLen, g_MinRestSec, g_MaxRestSec;
int g_AveWaitTime = 0;

void init(int &, int &);
void input_via_file(int, int &, string &, int &);
void input_via_keyboard(int, int &, string &, int &);
void output_via_file(int, int, int);
void output_via_keyboard(int, int, int);
void check_quit(int &);
void state_trans(const string &);
void rest_or_not(int &, const string &);
void allo_cust(int &);
void come_in_cust(int &, int);

int g_Time = 0;

int main() {
	int State = ON_DUTY, QueueNum = 0, in = 0, out = 0;
	string CurTimeRequestOfWindows(MAX_WINDOWS, '0');
	init(in, out);
	int CurTimeNumOfCustCome = 0;
	while (State) {
		++g_Time;
		//cout << Time << endl;
		//init();
		if (in) {
			input_via_keyboard(g_Time, CurTimeNumOfCustCome, CurTimeRequestOfWindows, State);
		}
		else {
			input_via_file(g_Time, CurTimeNumOfCustCome, CurTimeRequestOfWindows, State);
		}
		//process();
		rest_or_not(QueueNum, CurTimeRequestOfWindows);
		allo_cust(QueueNum);
		come_in_cust(QueueNum, CurTimeNumOfCustCome);
		state_trans(CurTimeRequestOfWindows);
		check_quit(State);
		//output();
		if (out) {
			output_via_keyboard(g_Time, QueueNum, State);
		}
		else {
			output_via_file(g_Time, QueueNum, State);
		}
	}
	cout << "Completed, please check the program log" << endl;
	system("pause");
	return 0;
}
