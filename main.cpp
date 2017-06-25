#include "Definition.h"
#include <thread>
#include <mutex>

using namespace std;

struct WindowsPort g_windows[MAX_WINDOWS] = { 0 };
int g_MaxCustSingleLine, g_MaxLines, g_MaxSeqLen, g_MinTimeLen, g_MaxTimeLen, g_MinRestSec, g_MaxRestSec;
int g_AveWaitTime = 0, g_Time = 0;
int g_state = ON_DUTY, g_QueueNum = 0, g_in_mode = 0;
mutex g_m;

//void init(int &, int &);
void init_graph();
void input(int &, string &, int &, int);
//void output(int, int, int);
void check_quit();
void state_trans(const string &);
void rest_or_not(int &, const string &);
void allo_cust(int &, const string &);
void come_in_cust(int &, int);
void dynamic_windows(const int, string &);
void read_char();

int main() {
	//init(in, out);
	init_graph();
	while (g_state) {
		++g_Time;
		//初始化当前时间输入数据
		string CurTimeRequestOfWindows(MAX_WINDOWS, '0');
		int CurTimeNumOfCustCome = 0;
		//pause
		this_thread::sleep_for(chrono::seconds(1));
		g_m.lock();
		//input
		input(CurTimeNumOfCustCome, CurTimeRequestOfWindows, g_state, g_in_mode);
		//process
		rest_or_not(g_QueueNum, CurTimeRequestOfWindows);
		dynamic_windows(g_QueueNum, CurTimeRequestOfWindows);
		allo_cust(g_QueueNum, CurTimeRequestOfWindows);
		come_in_cust(g_QueueNum, CurTimeNumOfCustCome);
		state_trans(CurTimeRequestOfWindows);
		check_quit();
		g_m.unlock();
		//output
		//output(QueueNum, State, out);
	}
	/*
	//echo
	if (out) {
		cout << "Completed, please check the output";
	}
	else {
		cout << "Completed, please check the program log file";
	}
	cout << endl;
	system("pause");
	*/
	return 0;
}
