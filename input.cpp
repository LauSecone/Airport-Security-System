#include "Definition.h"

using namespace std;

extern int g_Time;

void input_via_file(int &CurTimeNumOfCustCome, string &CurTimeRequestOfWindows, int &state) {
	//�������°������������
	if (state == WAIT_FOR_QUIT) return;
	//�������ʼ����ر���
	static string s_RequestOfWindows(MAX_WINDOWS, '0');
	static int s_NumOfCustCome = 0, s_ProcessTime = 0, s_status = state;
	CurTimeRequestOfWindows.assign(MAX_WINDOWS, '0');
	CurTimeNumOfCustCome = 0;
	//������������Ѿ���ʱ����ȡ�µ�����
	if ((s_ProcessTime < g_Time) && (s_NumOfCustCome == 0)) {
		char ch;
		//�����ļ�������
		static ifstream fin("input.dat", ifstream::in);
		//���ɹ���������д�����޷�������跴��
		if (fin) {
			fin >> ch >> ch >> s_ProcessTime;
			string str;
			fin >> str;
			char sta = '0';
			for (auto iter : str) {
				switch (iter) {
				case 'G': ++s_NumOfCustCome; break;
				case 'C': sta = 'C'; break;
				case 'R': sta = 'R'; break;
				case 'Q': s_status = WAIT_FOR_QUIT; break;
				}
				if (isdigit(iter)) {
					s_RequestOfWindows[iter - '0'] = sta;
				}
			}
		}
		else {
			cout << "Can't open the Input Data." << endl;
		}
	}
	//�����������ǡ���ǵ�ǰʱ�䣬����
	if (s_ProcessTime == g_Time) {
		CurTimeRequestOfWindows = s_RequestOfWindows;
		CurTimeNumOfCustCome = s_NumOfCustCome;
		state = s_status;
		s_NumOfCustCome = 0;
		s_RequestOfWindows.assign(MAX_WINDOWS, '0');
	}
	return;
}

void input_via_keyboard(int &CurTimeNumOfCustCome, string &CurTimeRequestOfWindows, int &state) {
	//�������°������������
	if (state == WAIT_FOR_QUIT) return;
	//�������ʼ����ر���
	static string s_RequestOfWindows(MAX_WINDOWS, '0');
	static int s_NumOfCustCome = 0, s_ProcessTime = 0, s_status = state;
	CurTimeRequestOfWindows.assign(MAX_WINDOWS, '0');
	CurTimeNumOfCustCome = 0;
	//������������Ѿ���ʱ����ȡ�µ�����
	if ((s_ProcessTime < g_Time) && (s_NumOfCustCome == 0)) {
		cout << "T = ";
		cin  >> s_ProcessTime;
		cout << "EVENT = ";
		string str;
		cin >> str;
		char sta = '0';
		for (auto iter : str) {
			switch (iter) {
			case 'G': ++s_NumOfCustCome; break;
			case 'C': sta = 'C'; break;
			case 'R': sta = 'R'; break;
			case 'Q': s_status = WAIT_FOR_QUIT; break;
			}
			if (isdigit(iter)) {
				s_RequestOfWindows[iter - '0'] = sta;
			}
		}
	}
	//�����������ǡ���ǵ�ǰʱ�䣬����
	if (s_ProcessTime == g_Time) {
		CurTimeRequestOfWindows = s_RequestOfWindows;
		CurTimeNumOfCustCome = s_NumOfCustCome;
		state = s_status;
		s_NumOfCustCome = 0;
		s_RequestOfWindows.assign(MAX_WINDOWS, '0');
	}
	return;
}