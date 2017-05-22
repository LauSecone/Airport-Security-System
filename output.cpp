#include <cmath>
#include <fstream>
#include "Definition.h"

using namespace std;

template <class TYPE>
int isequal(const TYPE &, const TYPE &);

void output(int Time, int QueueNum, int State) {
	cout << "Time is " << Time << endl;
	cout << "OFFDUTY=";
	if (State == 0) {
		cout << "Y" << endl;
	}
	else {
		cout << "N" << endl;
	}
	cout << "No.	State	CurNum	CurCustTime	WinListCustCount	Tot	ScheRestTime	TotOffTime" << endl;
	for (int i = 1; i <= REAL_WINDOWS; ++i) {
		cout << i << "	" << windows[i].State;
		cout << "	" << windows[i].CurNum
			<< "		" << windows[i].CurCustTime
			<< "		" << windows[i].CurNum
			<< "		" << windows[i].TotNum
			<< "	" << windows[i].ScheRestTime
			<< "	" << windows[i].TotOffTime;
		cout << endl;
	}
	cout << "ListLines = " << (ceil(QueueNum / MaxCustSingleLine) != 0 ? ceil(QueueNum / MaxCustSingleLine) : 1) << endl;
	cout << "ListCustCount = " << QueueNum << endl << endl;
}