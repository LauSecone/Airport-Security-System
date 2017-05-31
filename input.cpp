#include "Definition.h"

using namespace std;

void input_via_file(const int Time, int &CurTimeNumOfCustCome, string &CurTimeRequestOfWindows, int &state) {
	if (state == WAIT_FOR_QUIT) return;
	static string RequestOfWindows(MAX_WINDOWS, '0');
	static int NumOfCustCome = 0, ProcessTime = 0, status = state;
	CurTimeRequestOfWindows.assign(MAX_WINDOWS, '0');
	CurTimeNumOfCustCome = 0;
	if ((ProcessTime < Time) && (NumOfCustCome == 0)) {
		char ch;
		static ifstream fin("input.dat", ifstream::in);
		if (fin) {
			fin >> ch >> ch >> ProcessTime;
			string str;
			fin >> str;
			char sta = '0';
			for (auto iter : str) {
				switch (iter) {
				case 'G': ++NumOfCustCome; break;
				case 'C': sta = 'C'; break;
				case 'R': sta = 'R'; break;
				case 'Q': status = WAIT_FOR_QUIT; break;
				}
				if (isdigit(iter)) {
					RequestOfWindows[iter - '0'] = sta;
				}
			}
		}
		else {
			cout << "Can't open the Input Data." << endl;
		}
	}
	if (ProcessTime == Time) {
		CurTimeRequestOfWindows = RequestOfWindows;
		CurTimeNumOfCustCome = NumOfCustCome;
		state = status;
		NumOfCustCome = 0;
		RequestOfWindows.assign(MAX_WINDOWS, '0');
	}
	return;
}

void input_via_keyboard(const int Time, int &CurTimeNumOfCustCome, string &CurTimeRequestOfWindows, int &state) {
	if (state == WAIT_FOR_QUIT) return;
	static string RequestOfWindows(MAX_WINDOWS, '0');
	static int NumOfCustCome = 0, ProcessTime = 0, status = state;
	CurTimeRequestOfWindows.assign(MAX_WINDOWS, '0');
	CurTimeNumOfCustCome = 0;
	if ((ProcessTime < Time) && (NumOfCustCome == 0)) {
		char ch;
		cin >> ch >> ch >> ProcessTime;
		string str;
		cin >> str;
		char sta = '0';
		for (auto iter : str) {
			switch (iter) {
			case 'G': ++NumOfCustCome; break;
			case 'C': sta = 'C'; break;
			case 'R': sta = 'R'; break;
			case 'Q': status = WAIT_FOR_QUIT; break;
			}
			if (isdigit(iter)) {
				RequestOfWindows[iter - '0'] = sta;
			}
		}
	}
	if (ProcessTime == Time) {
		CurTimeRequestOfWindows = RequestOfWindows;
		CurTimeNumOfCustCome = NumOfCustCome;
		state = status;
		NumOfCustCome = 0;
		RequestOfWindows.assign(MAX_WINDOWS, '0');
	}
	return;
}