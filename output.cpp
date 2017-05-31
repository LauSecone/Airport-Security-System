#include <cmath>
#include <fstream>
#include "Definition.h"

using namespace std;

template <class TYPE>
int isequal(const TYPE &, const TYPE &);

void output(const int Time, const int QueueNum, const int State) {
	static ofstream fout("output.log", ofstream::out);
	static ofstream foutD("outputDetail.log", ofstream::out);
	static struct WindowsPort windowsBU[MAX_WINDOWS] = { 0 };
	if (fout) {
		fout << "Time is " << Time << endl;
		fout << "OFFDUTY=";
		if (State == 0) {
			fout << "Y" << endl;
		}
		else {
			fout << "N" << endl;
		}
		fout << "No.	State	CurNum	CurCustTime	WinListCustCount	Tot	ScheRestTime	TotOffTime" << endl;
		for (int i = 1; i <= REAL_WINDOWS; ++i) {
			fout << i << "	" << windows[i].State;
			fout << "	" << windows[i].CurNum
				<< "		" << windows[i].CurCustTime
				<< "		" << windows[i].CurNum
				<< "		" << windows[i].TotNum
				<< "	" << windows[i].ScheRestTime
				<< "		" << windows[i].TotOffTime;
			fout << endl;
		}
		fout << "ListLines = " << (ceil(QueueNum / MaxCustSingleLine) != 0 ? ceil(QueueNum / MaxCustSingleLine) : 1) << endl;
		fout << "ListCustCount = " << QueueNum << endl << endl;
	}
	else {
		cout << "Can't record the Output Log." << endl;
	}
	if (foutD) {
		if (!isequal(windowsBU, windows)) {
			for (int i = 0; i < MAX_WINDOWS; ++i) {
				windowsBU[i] = windows[i];
			}
			foutD << "Time is " << Time << endl;
			foutD << "OFFDUTY=";
			if (State == 0) {
				foutD << "Y" << endl;
			}
			else {
				foutD << "N" << endl;
			}
			foutD << "No.	State	CurNum	CurCustTime	WinListCustCount	Tot	ScheRestTime	TotOffTime" << endl;
			for (int i = 1; i <= REAL_WINDOWS; ++i) {
				foutD << i << "	" << windows[i].State;
				foutD << "	" << windows[i].CurNum
					<< "		" << windows[i].CurCustTime
					<< "		" << windows[i].CurNum
					<< "		" << windows[i].TotNum
					<< "	" << windows[i].ScheRestTime
					<< "		" << windows[i].TotOffTime;
				foutD << endl;
			}
			foutD << "ListLines = " << (ceil(QueueNum / MaxCustSingleLine) != 0 ? ceil(QueueNum / MaxCustSingleLine) : 1) << endl;
			foutD << "ListCustCount = " << QueueNum << endl << endl;
		}
	}
	else {
		cout << "Can't reocord the OutputDetail Log" << endl;
	}
}

template <class TYPE>
int isequal(const TYPE &x, const TYPE &y) {
	for (int i = 0; i < MAX_WINDOWS; ++i) {
		if ((x[i].CurNum != y[i].CurNum) || (x[i].State != y[i].State)) {
			return 0;
		}
	}
	return 1;
}

/*
template <class TYPE>
int isequal(const TYPE &data1, const TYPE &data2) {
	return (memcmp(reinterpret_cast<const void *>(&data1), reinterpret_cast<const void *>(&data2), sizeof(TYPE)) == 0);
}
*/