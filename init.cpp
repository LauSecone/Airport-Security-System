#include "graphics.h"
#include "Definition.h"
#include "PosiDef.h"
#include <iostream>
#include <fstream>

using namespace std;

void set_lamda_quittime(double, int);
void set_lamda(double);
void print_cfg(int);
void judge_iod(int &, int, int, mouse_msg);
void choose_mode(int &, int, int, mouse_msg, int);
int on_button(int, int, int, int, int, int);
void reflesh_panel(int, int);

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
	cout << "Please choose read method:(default is keyboard)" << endl 
		<< "1. Read via file 2. Read via keyboard 3.Creat date via Poison 4.Using Multithreading" << endl 
		<< "Please write the number 1 / 2 / 3 or 4:";
	cin >> in;
	if (in < 1 && in > 4) {
		cout << "Error read method, default set as via keyboard";
		in = 1;
	}
	--in;
	if (in == CREAT_VIA_POISSON) {
		cout << "Please input lamda :";
		double lamda;
		cin >> lamda;
		cout << "Please input quit time :";
		int QuitTime;
		cin >> QuitTime;
		set_lamda_quittime(lamda, QuitTime);
	}
	cout << endl;
	cout << "Please choose write method:(default is monitor)" << endl 
		<< "1. Write via file 2. Write via monitor" << endl 
		<< "Please write the number 1 or 2 :";
	cin >> out;
	if (out < 1 && out > 2) {
		cout << "Error write method, default set as via monitor";
		out = 1;
	}
	--out;
	cout << endl;
	return;
}

void init_graph(int &in_mode) {
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
		//cout << "The Config File has been read." << endl;
		fin.close();
	}
	else {
		//若打开文件有误，则置为默认状态，使程序可以继续执行
		//cout << "Can't open the Config File. But we set the default data." << endl;
		g_MaxCustSingleLine = 30;
		g_MaxLines = 8;
		g_MaxSeqLen = 10;
		g_MinTimeLen = 2;
		g_MaxTimeLen = 5;
		g_MinRestSec = 2;
		g_MaxRestSec = 5;
	}
	//show choose graph
	initgraph(SCREEN_X, SCREEN_Y);
	PIMAGE img = newimage();
	getimage(img, "choose.png");
	putimage(0, 0, img);
	delimage(img);
	int lamda = 1;
	//get mouse input
	in_mode = 0;
	while (!in_mode) {
		print_cfg(lamda);
		mouse_msg msg = { 0 };
		msg = getmouse();
		flushmouse();
		judge_iod(g_MaxCustSingleLine, MCSL_X, MCSL_Y, msg);
		judge_iod(g_MaxLines, ML_X, ML_Y, msg);
		judge_iod(g_MaxSeqLen, MSL_X, MSL_Y, msg);
		judge_iod(g_MaxTimeLen, MAXTL_X, MAXTL_Y, msg);
		judge_iod(g_MinTimeLen, MINTL_X, MINTL_Y, msg);
		judge_iod(g_MaxRestSec, MAXRS_X, MAXRS_Y, msg);
		judge_iod(g_MinRestSec, MINRS_X, MINRS_Y, msg);
		judge_iod(lamda, L_X, L_Y, msg);
		choose_mode(in_mode, RVF_X, RVF_Y, msg, 1);
		choose_mode(in_mode, RVS_X, RVS_Y, msg, 5);
		choose_mode(in_mode, CVP_X, CVP_Y, msg, 6);
	}
	--in_mode;
	if (in_mode == CREAT_VIA_POISSON) {

	}
	set_lamda(lamda);
	reflesh_panel(ON_DUTY, in_mode);
	return;
}

void print_cfg(int lamda) {  
	setcolor(EGERGB(0x0, 0xFF, 0x0));
	setfont(NUM_SIZE, 0, "serif");
	xyprintf(MAXTL_X + (S_LEN / 2), MAXTL_Y, "%d", g_MaxTimeLen);
	xyprintf(MINTL_X + (S_LEN / 2), MINTL_Y, "%d", g_MinTimeLen);
	xyprintf(MAXRS_X + (S_LEN / 2), MAXRS_Y, "%d", g_MaxRestSec);
	xyprintf(MINRS_X + (S_LEN / 2), MINRS_Y, "%d", g_MinRestSec);
	xyprintf(MCSL_X + (S_LEN / 2), MCSL_Y, "%d", g_MaxCustSingleLine);
	xyprintf(ML_X + (S_LEN / 2), ML_Y, "%d", g_MaxLines);
	xyprintf(MSL_X + (S_LEN / 2), MSL_Y, "%d", g_MaxSeqLen);
	xyprintf(L_X + (S_LEN / 2), L_Y, "%d", lamda);
}

void judge_iod(int &num, int x, int y, mouse_msg msg) {
	if (msg.is_left() && msg.is_up()) {
		if (on_button(msg.x, msg.y, x, x + SS_LEN, y, y + SS_LEN)) {
			--num;
		}
		if (on_button(msg.x, msg.y, x + S_LEN, x + S_LEN + SS_LEN, y, y + SS_LEN)) {
			++num;
		}
	}
	return;
}

void choose_mode(int &in_mode, int x, int y, mouse_msg msg, int mode) {
	if (msg.is_left() && msg.is_up() && on_button(msg.x, msg.y, x, x + CBX, y, y + CBY)) {
		in_mode = mode;
	}
}

int on_button(int x, int y, int x1, int x2, int y1, int y2) {
	return (x1 <= x && x <= x2 && y1 <= y && y <= y2);
}