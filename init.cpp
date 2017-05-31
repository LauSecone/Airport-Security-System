#include "Definition.h"

using namespace std;

void init(int &in, int &out) {
	for (int i = 1; i <= INIT_OPEN_WINDOWS; ++i) {
		windows[i].State = AVAILABLE_PORT;
	}
	for (int i = (INIT_OPEN_WINDOWS + 1); i <= REAL_WINDOWS; ++i) {
		windows[i].State = CLOSE_PORT;
	}
	string s;
	ifstream fin("cfgFile.cfg", ifstream::in);
	if (fin) {
		fin >> s >> MaxCustSingleLine >> s >> MaxLines >> s >> MaxSeqLen >> s >> MinTimeLen
			>> s >> MaxTimeLen >> s >> MinRestSec >> s >> MaxRestSec;
		cout << "The Config File has been readed." << endl;
		fin.close();
	}
	else {
		cout << "Can't open the Config File. But we set the default data." << endl;
		MaxCustSingleLine = 30;
		MaxLines = 8;
		MaxSeqLen = 10;
		MinTimeLen = 2;
		MaxTimeLen = 5;
		MinRestSec = 2;
		MaxRestSec = 5;

	}
	cout << "Please choose read method:(default is keyboard)" << endl << "1. Read via keyboard 2. Read via file" << endl << "Please write the number 1 or 2" << endl;
	cin >> in;
	--in;
	cout << "Please choose write method:(default is keyboard)" << endl << "1. Write via keyboard 2. Write via file" << endl << "Please write the number 1 or 2" << endl;
	cin >> out;
	--out;
	return;
}