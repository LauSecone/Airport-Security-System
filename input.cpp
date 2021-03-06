#include "PosiDef.h"
#include "Definition.h"
#include <random>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <iostream>

using namespace std;

extern int g_Time;

static string s_RequestOfWindows(MAX_WINDOWS, '0'), str;
static int s_NumOfCustCome = 0, s_ProcessTime = 0, s_status = ON_DUTY;
static double s_lamda = 1;
static int s_quittime = 0;

void process_request_string(string &);
void set_lamda_quittime(double, int);
void read_char();
int on_button(int, int, int, int, int, int);
void push_data(string &, int &, int &);

void input(int &CurTimeNumOfCustCome, string &CurTimeRequestOfWindows, int &state, int in_mode) {
	//若发出下班命令，跳过读入
	if (state == WAIT_FOR_QUIT) return;
	if (in_mode == READ_VIA_FILE) {
		CurTimeRequestOfWindows.assign(MAX_WINDOWS, '0');
		CurTimeNumOfCustCome = 0;
		//若保存的数据已经过时，读取新的数据
		if ((s_ProcessTime < g_Time) && (s_NumOfCustCome == 0)) {
			char ch;
			//定义文件输入流
			static ifstream fin("input.dat", ifstream::in);
			//若成功打开正常读写，若无法打开则给予反馈
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
		//若保存的数据恰好是当前时间，推送
		if (s_ProcessTime == g_Time) {
			push_data(CurTimeRequestOfWindows, CurTimeNumOfCustCome, state);
		}
		return;
	}
	if (in_mode == READ_VIA_KEYBOARD) {
		//清零与初始化相关变量
		CurTimeRequestOfWindows.assign(MAX_WINDOWS, '0');
		CurTimeNumOfCustCome = 0;
		//若保存的数据已经过时，读取新的数据
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
		//若保存的数据恰好是当前时间，推送
		if (s_ProcessTime == g_Time) {
			push_data(CurTimeRequestOfWindows, CurTimeNumOfCustCome, state);
		}
		return;
	}
	if (in_mode == CREAT_VIA_POISSON) {
		//清空数据
		CurTimeRequestOfWindows.assign(MAX_WINDOWS, '0');
		//用泊松分布生成到来乘客人数
		static poisson_distribution<int> s_p(s_lamda);
		static default_random_engine s_e((unsigned int)time(0));
		CurTimeNumOfCustCome = s_p(s_e);
		CurTimeRequestOfWindows = s_RequestOfWindows;
		s_RequestOfWindows.assign(MAX_WINDOWS, '0');
		//cout << "Poisson distribution number is " << CurTimeNumOfCustCome << endl;
		if (g_Time == s_quittime) {
			state = WAIT_FOR_QUIT;
		}
	}
	if (in_mode == READ_USE_THREAD) {
		//init
		CurTimeRequestOfWindows.assign(MAX_WINDOWS, '0');
		CurTimeNumOfCustCome = 0;
		//process input
		process_request_string(str);
		cout << endl;
		str.clear();
		//push input data
		push_data(CurTimeRequestOfWindows, CurTimeNumOfCustCome, state);
	}
	if (in_mode == READ_VIA_SCREEN) {
		//init
		CurTimeRequestOfWindows.assign(MAX_WINDOWS, '0');
		CurTimeNumOfCustCome = 0;
		//push the data
		push_data(CurTimeRequestOfWindows, CurTimeNumOfCustCome, state);
	}
	return;
}

void push_data(string &CurTimeRequestOfWindows, int &CurTimeNumOfCustCome, int &state) {
	CurTimeRequestOfWindows = s_RequestOfWindows;
	CurTimeNumOfCustCome = s_NumOfCustCome;
	state = s_status;
	//clean the cache
	s_NumOfCustCome = 0;
	s_RequestOfWindows.assign(MAX_WINDOWS, '0');
}

void process_request_string(string &str) {
	//convert string to data
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

void set_lamda_quittime(double lam, int quittime) {
	s_lamda = lam;
	s_quittime = quittime;
	return;
}

void set_lamda(double lam) {
	s_lamda = lam;
	return;
}

void read_char() {
	//use thread to get string
	while (s_status != WAIT_FOR_QUIT) {
		char ch;
		ch = (char)_getche();
		str = str + ch;
	}
	return;
}

void judge_rest(int x, int y, bool is_left, bool is_up, int mx, int my) {
	for (int num = 1; num <= REAL_WINDOWS; ++num) {
		if (is_left && is_up && on_button(mx, my, x, x + WX, y, y + WY)) {
			s_RequestOfWindows[num] = 'R';
		}
		y += WD_Y;
	}
	return;
}

void come_cust(int num, int x, int y, bool is_left, bool is_up, int mx, int my) {
	if (is_left && is_up && on_button(mx, my, x, x + EBX, y, y + EBY)) {
		s_NumOfCustCome += num;
	}
	return;
}

void judge_quit(int x, int y, bool is_left, bool is_up, int mx, int my) {
	if (is_left && is_up && on_button(mx, my, x, x + EBX, y, y + EBY)) {
		s_status = WAIT_FOR_QUIT;
		s_quittime = g_Time;
	}
	return;
}