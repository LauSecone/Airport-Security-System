#include "graphics.h"
#include "PosiDef.h"
#include "Definition.h"
#include <random>
#include <ctime>
#include <conio.h>
#include <thread>
#include <mutex>
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
void judge_rest(int, int, int, mouse_msg);
void come_cust(int, int, int, mouse_msg);
void judge_quit(int, int, mouse_msg);
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
		cout << "Poisson distribution number is " << CurTimeNumOfCustCome << endl;
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
	if (in_mode == READ_VIA_GRAPH) {
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
	while (s_status != WAIT_FOR_QUIT) {
		char ch;
		ch = (char)_getche();
		str = str + ch;
	}
	return;
}

void mouse_event() {
	mouse_msg msg = { 0 };
	while (s_status != WAIT_FOR_QUIT) {
		msg = getmouse();
		flushmouse();
		judge_rest(1, W1_X, W1_Y, msg);
		judge_rest(2, W2_X, W2_Y, msg);
		judge_rest(3, W3_X, W3_Y, msg);
		judge_rest(4, W4_X, W4_Y, msg);
		judge_rest(5, W5_X, W5_Y, msg);
		judge_rest(6, W6_X, W6_Y, msg);
		judge_rest(7, W7_X, W7_Y, msg);
		judge_rest(8, W8_X, W8_Y, msg);
		come_cust(1, CC1_X, CC1_Y, msg);
		come_cust(5, CC5_Y, CC5_Y, msg);
		judge_quit(Q_X, Q_Y, msg);
	}
	return;
}

void judge_rest(int num, int x, int y, mouse_msg msg) {
	if (msg.is_left() && msg.is_up() && on_button(msg.x, msg.y, x, x + WX, y, y + WY)) {
		s_RequestOfWindows[num] = 'R';
	}
	return;
}

void come_cust(int num, int x, int y, mouse_msg msg) {
	if (msg.is_left() && msg.is_up() && on_button(msg.x, msg.y, x, x + EBX, y, y + EBY)) {
		++s_NumOfCustCome;
	}
	return;
}

void judge_quit(int x, int y, mouse_msg msg) {
	if (msg.is_left() && msg.is_up() && on_button(msg.x, msg.y, x, x + EBX, y, y + EBY)) {
		s_status = WAIT_FOR_QUIT;
		s_quittime = g_Time;
	}
	return;
}