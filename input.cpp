#include "Definition.h"

using namespace std;

extern int g_Time;

void input_via_file(int &CurTimeNumOfCustCome, string &CurTimeRequestOfWindows, int &state) {
	//若发出下班命令，跳过读入
	if (state == WAIT_FOR_QUIT) return;
	//清零与初始化相关变量
	static string s_RequestOfWindows(MAX_WINDOWS, '0');
	static int s_NumOfCustCome = 0, s_ProcessTime = 0, s_status = state;
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
	//若保存的数据恰好是当前时间，推送
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
	//若发出下班命令，跳过读入
	if (state == WAIT_FOR_QUIT) return;
	//清零与初始化相关变量
	static string s_RequestOfWindows(MAX_WINDOWS, '0');
	static int s_NumOfCustCome = 0, s_ProcessTime = 0, s_status = state;
	CurTimeRequestOfWindows.assign(MAX_WINDOWS, '0');
	CurTimeNumOfCustCome = 0;
	//若保存的数据已经过时，读取新的数据
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
	//若保存的数据恰好是当前时间，推送
	if (s_ProcessTime == g_Time) {
		CurTimeRequestOfWindows = s_RequestOfWindows;
		CurTimeNumOfCustCome = s_NumOfCustCome;
		state = s_status;
		s_NumOfCustCome = 0;
		s_RequestOfWindows.assign(MAX_WINDOWS, '0');
	}
	return;
}