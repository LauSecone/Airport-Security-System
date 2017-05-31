#include "Definition.h"
using namespace std;

struct WindowsPort windows[MAX_WINDOWS] = { 0 };
int MaxCustSingleLine, MaxLines, MaxSeqLen, MinTimeLen, MaxTimeLen, MinRestSec, MaxRestSec;

void init();
void input(int, int *, string &, int *);
void output(int, int, int);
void check_quit(int *);
void state_trans(string);
void restornot(int *, string);
void allocust(int *);
void comeincust(int *, int);

int main() {
	int Time = 0;
	init();
	int State = ON_DUTY, QueueNum = 0;
	string CurTimeRequestOfWindows(MAX_WINDOWS, '0');
	int CurTimeNumOfCustCome = 0;
	while (State) {
		++Time;
		//init();
		input(Time, &CurTimeNumOfCustCome, CurTimeRequestOfWindows, &State);
		//process();
		restornot(&QueueNum, CurTimeRequestOfWindows);
		allocust(&QueueNum);
		comeincust(&QueueNum, CurTimeNumOfCustCome);
		state_trans(CurTimeRequestOfWindows);
		check_quit(&State);
		//output();
		output(Time, QueueNum, State);
	}
	cout << "Completed, please check the program log" << endl;
	system("pause");
	return 0;
}
