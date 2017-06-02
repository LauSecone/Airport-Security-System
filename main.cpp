#include "Definition.h"
using namespace std;

struct WindowsPort windows[MAX_WINDOWS] = { 0 };
int MaxCustSingleLine, MaxLines, MaxSeqLen, MinTimeLen, MaxTimeLen, MinRestSec, MaxRestSec;
int AveWaitTime;

void init(int &, int &);
void input_via_file(int, int &, string &, int &);
void input_via_keyboard(int, int &, string &, int &);
void output_via_file(int, int, int);
void output_via_keyboard(int, int, int);
void check_quit(int &);
void state_trans(const string &);
void restornot(int &, const string &);
void allocust(int &);
void comeincust(int &, int);

int main() {
	int Time = 0;
	int State = ON_DUTY, QueueNum = 0, in = 0, out = 0;
	string CurTimeRequestOfWindows(MAX_WINDOWS, '0');
	init(in, out);
	int CurTimeNumOfCustCome = 0;
	while (State) {
		++Time;
		//init();
		if (in) {
			input_via_keyboard(Time, CurTimeNumOfCustCome, CurTimeRequestOfWindows, State);
		}
		else {
			input_via_file(Time, CurTimeNumOfCustCome, CurTimeRequestOfWindows, State);
		}
		//process();
		restornot(QueueNum, CurTimeRequestOfWindows);
		allocust(QueueNum);
		comeincust(QueueNum, CurTimeNumOfCustCome);
		state_trans(CurTimeRequestOfWindows);
		check_quit(State);
		//cout << Time << ' ' << windows[4].CurStateTime << endl;
		//output();
		if (out) {
			output_via_keyboard(Time, QueueNum, State);
		}
		else {
			output_via_file(Time, QueueNum, State);
		}
	}
	cout << "Completed, please check the program log" << endl;
	system("pause");
	return 0;
}
