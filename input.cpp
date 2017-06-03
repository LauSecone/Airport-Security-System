#include <random>
#include <ctime>
#include "Definition.h"

using namespace std;

extern int g_Time;

static string s_RequestOfWindows(MAX_WINDOWS, '0');
static int s_NumOfCustCome = 0, s_ProcessTime = 0, s_status = ON_DUTY;
static double lamda = 1;

void process_request_string(string &);

void input(int &CurTimeNumOfCustCome, string &CurTimeRequestOfWindows, int &state, int in) {
	//�������°������������
	if (state == WAIT_FOR_QUIT) return;
	if (in == READ_VIA_FILE) {
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
				process_request_string(str);
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
	if (in == READ_VIA_KEYBOARD) {
		//�������ʼ����ر���
		CurTimeRequestOfWindows.assign(MAX_WINDOWS, '0');
		CurTimeNumOfCustCome = 0;
		//������������Ѿ���ʱ����ȡ�µ�����
		if ((s_ProcessTime < g_Time) && (s_NumOfCustCome == 0)) {
			cout << "T = ";
			cin >> s_ProcessTime;
			if (s_ProcessTime < g_Time) {
				cout << "Error input, default set input time as next time." << endl;
			}
			cout << "EVENT = ";
			string str;
			cin >> str;
			process_request_string(str);
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
	if (in == CREAT_VIA_POISSON) {
		//CurTimeNumOfCustCome
	}
}

void process_request_string(string &str) {
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
	return;
}