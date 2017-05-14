#include "Definition.h"

using namespace std;

struct WindowsPort windows[MAX_WINDOWS] = { 0 };
int MaxCustSingleLine, MaxLines, MaxSeqLen, MinTimeLen, MaxTimeLen, MinRestSec, MaxRestSec;

void init();
void input(int, int*, string &, int*);
void output(int, int, int);
void check_quit(int *);

int main() {
	int Time = 0;
	init();
	int State = ON_DUTY, QueueNum = 0;
	while (State) {
		++Time;
		string CurTimeRequestOfWindows(MAX_WINDOWS, '0');
		int CurTimeNumOfCustCome = 0;
		input(Time, &CurTimeNumOfCustCome, CurTimeRequestOfWindows, &State);
		//process();
		check_quit(&State);
		output(Time, QueueNum, State);
	}
	return 0;
}