#include <cmath>
#include <fstream>
#include "Definition.h"

using namespace std;

static struct WindowsPort windowsBU[MAX_WINDOWS] = { 0 };

int isequal(const int &);

void output_via_file(const int Time, const int QueueNum, const int State) {
	static ofstream fout("output.log", ofstream::out);
	static ofstream foutD("outputDetail.log", ofstream::out);
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
		if (!isequal(Time)) {
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

void output_via_keyboard(const int Time, const int QueueNum, const int State) {
	if (!isequal(Time)) {
		for (int i = 0; i < MAX_WINDOWS; ++i) {
			windowsBU[i] = windows[i];
		}
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
				<< "		" << windows[i].TotOffTime;
			cout << endl;
		}
		cout << "ListLines = " << (ceil(QueueNum / MaxCustSingleLine) != 0 ? ceil(QueueNum / MaxCustSingleLine) : 1) << endl;
		cout << "ListCustCount = " << QueueNum << endl << endl;
	}
}

int isequal(const int &Time) {
	if (Time == 1) return 0;
	for (int i = 0; i < MAX_WINDOWS; ++i) {
		if (windowsBU[i].CurNum != windows[i].CurNum) {
			return 0;
		}
	}
	return 1;
}