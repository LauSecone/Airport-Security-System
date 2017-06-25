#include "graphics.h"
#include "Definition.h"
#include "PosiDef.h"
#include <mutex>

using namespace std;

void reflesh_panel();
void block_button();
void judge_rest(int, int, bool, bool, int, int);
void come_cust(int, int, int, bool, bool, int, int);
void judge_quit(int, int, bool, bool, int, int);
void queue_graph();
void windows_graph();
void airport_state();
void wait_interval_display();
void time_display();
int rest_state(int);
void rest_display();
void winstate_display();
void queue_warning();
extern mutex g_m;

extern int g_state, g_QueueNum, g_in_mode, g_Time, g_AveWaitTime;

void graph_io() {
	setinitmode(INIT_ANIMATION);
	initgraph(SCREEN_X, SCREEN_Y);
	for (; is_run(); delay_fps(60)) {
		g_m.lock();
		//reflesh
		reflesh_panel();
		//display graph and data
		airport_state();
		wait_interval_display();
		time_display();
		queue_graph();
		windows_graph();
		rest_display();
		winstate_display();
		queue_warning();
		//deal mouse event
		mouse_msg msg = { 0 };
		if (mousemsg()) {
			msg = getmouse();
			flushmouse();
		}
		judge_rest(W_X, W_Y, msg.is_left(), msg.is_up(), msg.x, msg.y);
		if (g_in_mode == READ_VIA_SCREEN) {
			come_cust(1, CC1_X, CC1_Y, msg.is_left(), msg.is_up(), msg.x, msg.y);
			come_cust(5, CC5_X, CC5_Y, msg.is_left(), msg.is_up(), msg.x, msg.y);
		}
		if (g_in_mode == READ_VIA_SCREEN || g_in_mode == CREAT_VIA_POISSON) {
			judge_quit(Q_X, Q_Y, msg.is_left(), msg.is_up(), msg.x, msg.y);
		}
		g_m.unlock();
	}
	closegraph();
	g_state = OFF_DUTY;
	return;
}

void reflesh_panel() {
	//dispay panel
	PIMAGE img = newimage();
	getimage(img, "run.png");
	putimage(0, 0, img);
	delimage(img);
	extern int g_Time;
	//block unactive button
	block_button();
	return;
}

void block_button() {
	//use imagefilter_blurring to decrease brightness
	if (g_state == WAIT_FOR_QUIT || g_in_mode == READ_VIA_FILE) {
		imagefilter_blurring(NULL, 0x00, 0x50, Q_X, Q_Y, EBX, EBY);
	}
	for (int i = 0; i < REAL_WINDOWS; ++i) {
		if (g_windows[i + 1].State == CLOSE_PORT || g_windows[i + 1].RestSignal == 1 || g_windows[i + 1].State == RESTTING_PORT) {
			imagefilter_blurring(NULL, 0x00, 0x50, W_X, W_Y + WD_Y * i, WX, WY);
		}
	}
	if (g_in_mode == READ_VIA_FILE || g_in_mode == CREAT_VIA_POISSON || g_state == WAIT_FOR_QUIT) {
		imagefilter_blurring(NULL, 0x00, 0x50, CC1_X, CC1_Y, EBX, EBY);
		imagefilter_blurring(NULL, 0x00, 0x50, CC5_X, CC5_Y, EBX, EBY);
	}
	return;
}

/*
PIMAGE img = newimage();
getimage(img, "cust.png");
putimage(0, 0, img);
delimage(img);
*/
void queue_graph() {
	int quenum;
	quenum = g_QueueNum;
	PIMAGE img = newimage();
	getimage(img, "cust.png");
	setbkcolor(EGERGB(37, 37, 37));
	setcolor(EGERGB(81, 81, 81));
	line(TOPLEFT_X, TOPLEFT_Y, TOPLEFT_X + SPACING + g_MaxCustSingleLine*(2 * RADIUS + SPACING), TOPLEFT_Y);
	line(TOPLEFT_X, TOPLEFT_Y, TOPLEFT_X, TOPLEFT_Y + g_MaxLines*(2 * RADIUS + SPACING));
	line(TOPLEFT_X + SPACING + g_MaxCustSingleLine*(2 * RADIUS + SPACING), TOPLEFT_Y + (2 * RADIUS + SPACING), TOPLEFT_X + SPACING + g_MaxCustSingleLine*(2 * RADIUS + SPACING), TOPLEFT_Y + g_MaxLines*(2 * RADIUS + SPACING));
	if (g_MaxLines % 2 == 0)
		line(TOPLEFT_X, TOPLEFT_Y + g_MaxLines*(2 * RADIUS + SPACING), TOPLEFT_X + g_MaxCustSingleLine*(2 * RADIUS + SPACING) - 2 * RADIUS, TOPLEFT_Y + g_MaxLines*(2 * RADIUS + SPACING));
	else
		line(TOPLEFT_X + (2 * RADIUS + SPACING), TOPLEFT_Y + g_MaxLines*(2 * RADIUS + SPACING), TOPLEFT_X + SPACING + g_MaxCustSingleLine*(2 * RADIUS + SPACING), TOPLEFT_Y + g_MaxLines*(2 * RADIUS + SPACING));
	int i, j, dottedline[40];
	for (i = 1; i <= g_MaxLines - 1; i++) {
		for (j = 1; j <= g_MaxCustSingleLine - 2; j++) {
			dottedline[4 * j - 4] = TOPLEFT_X + j*(2 * RADIUS + SPACING) + SPACING;
			dottedline[4 * j - 3] = TOPLEFT_Y + i*(2 * RADIUS + SPACING);
			dottedline[4 * j - 2] = TOPLEFT_X + SPACING + DOTTEDLEN + j*(2 * RADIUS + SPACING);
			dottedline[4 * j - 1] = TOPLEFT_Y + i*(2 * RADIUS + SPACING);
		}
		drawlines(g_MaxCustSingleLine - 2, dottedline);
	}
	for (i = 1; i <= g_MaxLines && quenum > 0; i++)
	{
		if (i % 2) {
			setcolor(EGERGB(81, 81, 81));
			line(TOPLEFT_X + g_MaxCustSingleLine*(2 * RADIUS + SPACING) - 2 * RADIUS, TOPLEFT_Y + i*(2 * RADIUS + SPACING), TOPLEFT_X - 2 * RADIUS + DOTTEDLEN + g_MaxCustSingleLine*(2 * RADIUS + SPACING), TOPLEFT_Y + i*(2 * RADIUS + SPACING));
			//setcolor(EGERGB(255, 255, 255));
			//setfillcolor(EGERGB(0, 0, 0));
			for (j = g_MaxCustSingleLine; j >= 1 && quenum  > 0; j--) {
				putimage(TOPLEFT_X - RADIUS + j*(2 * RADIUS + SPACING) - RADIUS, TOPLEFT_Y - RADIUS - SPACING / 2 + i*(2 * RADIUS + SPACING) - RADIUS, img);
				//circle(TOPLEFT_X - RADIUS + j*(2 * RADIUS + SPACING), TOPLEFT_Y - RADIUS - SPACING / 2 + i*(2 * RADIUS + SPACING), RADIUS);
				//floodfill(TOPLEFT_X - RADIUS + j*(2 * RADIUS + SPACING), TOPLEFT_Y - RADIUS - SPACING / 2 + i*(2 * RADIUS + SPACING), EGERGB(255, 255, 255));
				quenum--;
			}
		}
		else {
			setcolor(EGERGB(81, 81, 81));
			line(TOPLEFT_X + SPACING, TOPLEFT_Y + i*(2 * RADIUS + SPACING), TOPLEFT_X + SPACING + DOTTEDLEN, TOPLEFT_Y + i*(2 * RADIUS + SPACING));
			//setcolor(EGERGB(255, 255, 255));
			//setfillcolor(EGERGB(0, 0, 0));
			for (j = 1; j <= g_MaxCustSingleLine && quenum  > 0; j++) {
				putimage(TOPLEFT_X - RADIUS + j*(2 * RADIUS + SPACING) - RADIUS, TOPLEFT_Y - RADIUS - SPACING / 2 + i*(2 * RADIUS + SPACING) - RADIUS, img);
				//circle(TOPLEFT_X - RADIUS + j*(2 * RADIUS + SPACING), TOPLEFT_Y - RADIUS - SPACING / 2 + i*(2 * RADIUS + SPACING), RADIUS);
				//floodfill(TOPLEFT_X - RADIUS + j*(2 * RADIUS + SPACING), TOPLEFT_Y - RADIUS - SPACING / 2 + i*(2 * RADIUS + SPACING), EGERGB(255, 255, 255));
				quenum--;
			}
		}
	}
	delimage(img);
}

void windows_graph() {
	PIMAGE img = newimage();
	getimage(img, "cust.png");
	for (int i = 1; i <= 8; ++i) {
		if (g_windows[i].State != RESTTING_PORT && g_windows[i].State != CLOSE_PORT)
			for (int j = 1; j <= g_windows[i].CurNum; ++j) {
				//setcolor(EGERGB(255, 0, 255));
				//setfillcolor(EGERGB(0, 0, 205));
				//circle(WIN_X - (j*SPACING + (j - 1) * 2 * RADIUS + RADIUS), WIN_Y + (i - 1) * WIN_SPACE + SPACING / 2 + RADIUS, RADIUS);
				//floodfill(WIN_X - (j*SPACING + (j - 1) * 2 * RADIUS + RADIUS), WIN_Y + (i - 1) * WIN_SPACE + SPACING / 2 + RADIUS, EGERGB(255, 0, 255));
				putimage(WIN_X - (j*SPACING + (j - 1) * 2 * RADIUS + RADIUS)-RADIUS, WIN_Y + (i - 1) * WIN_SPACE + SPACING / 2 + RADIUS-RADIUS, img);
			}
	}
	delimage(img);
}
void airport_state() {
	setcolor(EGERGB(255, 255, 255));
	setfont(NUM_SIZE, 0, TYPEFACE);
	switch (g_state) {
	case 0: outtextxy(650, 630, "机场状态：已经下班"); break;
	case 1: outtextxy(650, 630, "机场状态：正常上班"); break;
	case 2: outtextxy(650, 630, "机场状态：等待下班"); break;
	}
}
void winstate_display() {
	setcolor(EGERGB(255, 255, 255));
	setfont(NUM_SIZE, 0, TYPEFACE);
	setbkmode(TRANSPARENT);
	for (int i = 1; i <= 8; ++i) {
		switch (g_windows[i].State) {
		case AVAILABLE_PORT: outtextxy(990, 72 + (i - 1) * WIN_SPACE, "空闲中"); break;
		case CHECKING_PORT : outtextxy(990, 72 + (i - 1) * WIN_SPACE, "工作中"); break;
		case SWITCHING_PORT: outtextxy(990, 72 + (i - 1) * WIN_SPACE, "转换中"); break;
		case RESTTING_PORT : outtextxy(990, 72 + (i - 1) * WIN_SPACE, "休息中"); break;
		case CLOSE_PORT    : outtextxy(990, 72 + (i - 1) * WIN_SPACE, "已关闭"); break;
		}
	}
}

void rest_display() {
	setcolor(EGERGB(255, 255, 255));
	setfont(NUM_SIZE, 0, TYPEFACE);
	for (int i = 1; i <= 8; ++i) {
		if (rest_state(i))
			outtextxy(REST_SIGNAL_X, REST_SIGNAL_Y + (i - 1) * WIN_SPACE, "未批准");
	}
}

void wait_interval_display() {
	setcolor(EGERGB(255, 255, 255));
	setfont(NUM_SIZE, 0, TYPEFACE);
	outtextxy(255, 560, "乘客平均等待时间：");
	char s[4];
	sprintf(s, "%d", g_AveWaitTime);
	outtextxy(393, 560, s);
}

void queue_warning() {
	setcolor(EGERGB(255, 255, 255));
	setfont(NUM_SIZE, 0, TYPEFACE);
	if (g_QueueNum == g_MaxCustSingleLine * g_MaxLines)
		outtextxy(265, 20, "缓冲区已满");
}

void time_display() {
	setcolor(EGERGB(255, 255, 255));
	setfont(NUM_SIZE, 0, TYPEFACE);
	outtextxy(1090, 10, "当前时间：");
	char s[5];
	sprintf(s, "%d", g_Time);
	outtextxy(1165, 10, s);
}