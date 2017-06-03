#include "Definition.h"

using namespace std;

void set_lamda(double);

void init(int &in, int &out) {
	//��ǰ�ĸ��������Ϊ����
	for (int i = 1; i <= INIT_OPEN_WINDOWS; ++i) {
		g_windows[i].State = AVAILABLE_PORT;
	}
	//�����ĸ��������Ϊ�ر�
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
		//�����ļ���������ΪĬ��״̬��ʹ������Լ���ִ��
		cout << "Can't open the Config File. But we set the default data." << endl;
		g_MaxCustSingleLine = 30;
		g_MaxLines = 8;
		g_MaxSeqLen = 10;
		g_MinTimeLen = 2;
		g_MaxTimeLen = 5;
		g_MinRestSec = 2;
		g_MaxRestSec = 5;

	}
	//���û�ѡ�����������ʽ����������Ч���룬��Ĭ��ʹ�ü����������
	cout << "Please choose read method:(default is keyboard)" << endl << "1. Read via file 2. Read via keyboard 3.Creat date via Poison" << endl << "Please write the number 1 or 2" << endl;
	cin >> in;
	if (in < 1 && in > 3) {
		cout << "Error read method, default set as via keyboard";
		in = 1;
	}
	--in;
	if (in == CREAT_VIA_POISSON) {
		cout << "Please input lamda :";
		double lamda;
		cin >> lamda;
		set_lamda(lamda);
	}
	cout << "Please choose write method:(default is keyboard)" << endl << "1. Write via file 2. Write via keyboard" << endl << "Please write the number 1 or 2" << endl;
	cin >> out;
	if (out < 1 && out > 2) {
		cout << "Error write method, default set as via keyboard";
		out = 1;
	}
	--out;
	return;
}