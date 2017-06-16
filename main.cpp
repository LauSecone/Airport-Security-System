#include "Definition.h"
#include <thread>

using namespace std;

struct WindowsPort g_windows[MAX_WINDOWS] = { 0 };
int g_MaxCustSingleLine, g_MaxLines, g_MaxSeqLen, g_MinTimeLen, g_MaxTimeLen, g_MinRestSec, g_MaxRestSec;
int g_AveWaitTime = 0, g_Time = 0;

//void init(int &, int &);
void init_graph(int &);
void input(int &, string &, int &, int);
//void output(int, int, int);
void output_graph(int, int);
void check_quit(int &);
void state_trans(const string &);
void rest_or_not(int &, const string &);
void allo_cust(int &, const string &);
void come_in_cust(int &, int);
void dynamic_windows(const int, string &);
void read_char();
void mouse_event();

int main() {
	//init
	int State = ON_DUTY, QueueNum = 0, in_mode = 0;// out = 0;
	//init(in, out);
	init_graph(in_mode);
	if (in_mode == READ_VIA_GRAPH || in_mode == CREAT_VIA_POISSON) {
		thread get_input(mouse_event);
		get_input.detach();
	}
	while (State) {
		++g_Time;
		//初始化当前时间输入数据
		string CurTimeRequestOfWindows(MAX_WINDOWS, '0');
		int CurTimeNumOfCustCome = 0;
		//input
		input(CurTimeNumOfCustCome, CurTimeRequestOfWindows, State, in_mode);
		//process
		rest_or_not(QueueNum, CurTimeRequestOfWindows);
		dynamic_windows(QueueNum, CurTimeRequestOfWindows);
		allo_cust(QueueNum, CurTimeRequestOfWindows);
		come_in_cust(QueueNum, CurTimeNumOfCustCome);
		state_trans(CurTimeRequestOfWindows);
		check_quit(State);
		//output
		//output(QueueNum, State, out);
		output_graph(QueueNum, State);
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
