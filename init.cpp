#include "Definition.h"

using namespace std;

void init(int &in, int &out) {
	//将前四个安检口置为可用
	for (int i = 1; i <= INIT_OPEN_WINDOWS; ++i) {
		g_windows[i].State = AVAILABLE_PORT;
	}
	//将后四个安检口置为关闭
	for (int i = (INIT_OPEN_WINDOWS + 1); i <= REAL_WINDOWS; ++i) {
		g_windows[i].State = CLOSE_PORT;
	}
	string s;
	ifstream fin("cfgFile.cfg", ifstream::in);
	if (fin) {
		fin >> s >> g_MaxCustSingleLine >> s >> g_MaxLines >> s >> g_MaxSeqLen >> s >> g_MinTimeLen
			>> s >> g_MaxTimeLen >> s >> g_MinRestSec >> s >> g_MaxRestSec;
		cout << "The Config File has been read." << endl;
		fin.close();
	}
	else {
		//若打开文件有误，则置为默认状态，使程序可以继续执行
		cout << "Can't open the Config File. But we set the default data." << endl;
		g_MaxCustSingleLine = 30;
		g_MaxLines = 8;
		g_MaxSeqLen = 10;
		g_MinTimeLen = 2;
		g_MaxTimeLen = 5;
		g_MinRestSec = 2;
		g_MaxRestSec = 5;

	}
	//让用户选择输入输出方式。若出现无效输入，则默认使用键盘输入输出
	cout << "Please choose read method:(default is keyboard)" << endl << "1. Read via file 2. Read via keyboard" << endl << "Please write the number 1 or 2" << endl;
	cin >> in;
	--in;
	cout << "Please choose write method:(default is keyboard)" << endl << "1. Write via file 2. Write via keyboard" << endl << "Please write the number 1 or 2" << endl;
	cin >> out;
	--out;
	return;
}