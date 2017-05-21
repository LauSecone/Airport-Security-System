#include <cmath>
#include <fstream>
#include "memcmp.cpp"
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
	cout << "No.	State	CurNum	CurCustTime	WinListCustCount	Tot" << endl;
	for (int i = 1; i <= REAL_WINDOWS; ++i) {
		cout << i << "	" << windows[i].State;
		cout << "	" << windows[i].CurNum
			<< "		" << windows[i].CurCustTime
			<< "		" << windows[i].CurNum
			<< "		" << windows[i].TotNum;
		cout << endl;
	}
	cout << "ListLines = " << ceil(QueueNum / MaxCustSingleLine) << endl;
	cout << "ListCustCount = " << QueueNum << endl << endl;
}