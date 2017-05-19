#include <math.h>
#include "Definition.h"

using namespace std;

void output(int Time, int QueueNum, int State) {
	cout << "Time is " << Time << endl;
	cout << "OFFDUTY=";
	if (State == 0) {
		cout << "Y" << endl;
	}
	else {
		cout << "N" << endl;
	}
	cout << "No.	State	CurNum	CurCustTime	WinListCustCount" << endl;
	for (int i = 1; i <= 8; ++i) {
		cout << i << "	" << windows[i].State;
		if (windows[i].State == 5) {
			continue;
		}
		cout << "	" << windows[i].CurNum
			<< "		" << windows[i].CurCustTime
			<< "		" << windows[i].CurNum << endl;
	}
	cout << "ListLines = " << ceil(QueueNum / MaxCustSingleLine) << endl;
	cout << "ListCustCount = " << QueueNum << endl << endl;
}