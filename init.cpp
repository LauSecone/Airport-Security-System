#include "Definition.h"

using namespace std;

void init() {
	for (int i = 1; i <= 4; ++i) {
		windows[i].State = 1;
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
	MaxCustSingleLine *= 10;
	MaxLines *= 10;
	MaxSeqLen *= 10;
	MinTimeLen *= 10;
	MaxTimeLen *= 10;
	return;
}