#include <random>
#include <ctime>
#include <conio.h>
#include <thread>
#include <mutex>
#include "Definition.h"

using namespace std;

extern int g_Time;

static string s_RequestOfWindows(MAX_WINDOWS, '0'), str;
static int s_NumOfCustCome = 0, s_ProcessTime = 0, s_status = ON_DUTY;
static double s_lamda = 1;
static int s_quittime = 0;
extern mutex g_m;

void process_request_string(string &);
void set_lamda(double, int);
void read_char();

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
				fin >> str;
				process_request_string(str);
				str.clear();
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
			cin >> str;
			process_request_string(str);
			str.clear();
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
		//�������
		CurTimeRequestOfWindows.assign(MAX_WINDOWS, '0');
		//�ò��ɷֲ����ɵ����˿�����
		static poisson_distribution<int> s_p(s_lamda);
		static default_random_engine s_e((unsigned int)time(0));
		CurTimeNumOfCustCome = s_p(s_e);
		cout << "Poisson distribution number is " << CurTimeNumOfCustCome << endl;
		if (g_Time == s_quittime) {
			state = WAIT_FOR_QUIT;
		}
	}
	if (in == USE_THREAD) {
		this_thread::sleep_for(chrono::seconds(1));
		CurTimeRequestOfWindows.assign(MAX_WINDOWS, '0');
		CurTimeNumOfCustCome = 0;
		g_m.lock();
		process_request_string(str);
		str.clear();
		g_m.unlock();
		CurTimeRequestOfWindows = s_RequestOfWindows;
		CurTimeNumOfCustCome = s_NumOfCustCome;
		state = s_status;
		s_NumOfCustCome = 0;
		s_RequestOfWindows.assign(MAX_WINDOWS, '0');
	}
	return;
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

void set_lamda(double lam, int quittime) {
	s_lamda = lam;
	s_quittime = quittime;
	return;
}

void read_char() {
	while (s_status != WAIT_FOR_QUIT) {
		//g_m.lock();
		char ch;
		ch = (char)_getche();
		str = str + ch;
		//g_m.unlock();
	}
	return;
}