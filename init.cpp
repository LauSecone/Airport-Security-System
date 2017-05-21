#include<fstream>
#include "Definition.h"

using namespace std;

void init() {
	for (int i = 1; i <= INIT_OPEN_WINDOWS; ++i) {
		windows[i].State = AVAILABLE_PORT;
	}
	for (int i = (INIT_OPEN_WINDOWS + 1); i <= REAL_WINDOWS; ++i) {
		windows[i].State = CLOSE_PORT;
	}
	string s;
	ifstream fin("ConfigFile.cfg", ifstream::in);
	if (fin) {
		fin >> s >> MaxCustSingleLine >> s >> MaxLines >> s >> MaxSeqLen >> s >> MinTimeLen
			>> s >> MaxTimeLen >> s >> MinRestSec >> s >> MaxRestSec;
		cout << "The Config File has been readed." << endl;
		fin.close();
	}
	else {
		cout << "Can't open the Config File." << endl;
	}
	return;
}