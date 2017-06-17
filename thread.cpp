#include "graphics.h"
#include "Definition.h"
#include "PosiDef.h"

using namespace std;

void reflesh_panel();
void block_button();
void judge_rest(int, int, bool, bool, int, int);
void come_cust(int, int, int, bool, bool, int, int);
void judge_quit(int, int, bool, bool, int, int);

extern int g_state, g_QueueNum, g_in_mode, g_Time;

void graph_io() {
	setinitmode(INIT_ANIMATION);
	initgraph(SCREEN_X, SCREEN_Y);
	for (; is_run(); delay_fps(60)) {
		mouse_msg msg = { 0 };
		if (mousemsg()) {
			msg = getmouse();
			flushmouse();
		}
		judge_rest(W_X, W_Y, msg.is_left(), msg.is_up(), msg.x, msg.y);
		come_cust(1, CC1_X, CC1_Y, msg.is_left(), msg.is_up(), msg.x, msg.y);
		come_cust(5, CC5_Y, CC5_Y, msg.is_left(), msg.is_up(), msg.x, msg.y);
		judge_quit(Q_X, Q_Y, msg.is_left(), msg.is_up(), msg.x, msg.y);
		reflesh_panel();
		xyprintf(0, 0, "%3d", g_Time);

	}
	closegraph();
	return;
}

void reflesh_panel() {
	PIMAGE img = newimage();
	getimage(img, "run.png");
	putimage(0, 0, img);
	delimage(img);
	extern int g_Time;
	setcolor(EGERGB(0x00, 0xFF, 0x00));
	setfont(NUM_SIZE, 0, TYPEFACE);
	xyprintf(0, 0, "%3d", g_Time);
	block_button();
	return;
}

void block_button() {
	if (g_state == WAIT_FOR_QUIT) {
		imagefilter_blurring(NULL, 0x00, 0x50, Q_X, Q_Y, EBX, EBY);
	}
	for (int i = 0; i < REAL_WINDOWS; ++i) {
		if (g_windows[i + 1].State == CLOSE_PORT || g_windows[i + 1].RestSignal == 1 || g_windows[i + 1].State == RESTTING_PORT) {
			imagefilter_blurring(NULL, 0x00, 0x50, W_X, W_Y + WD_Y * i, WX, WY);
		}
	}
	if (g_in_mode == CREAT_VIA_POISSON) {
		imagefilter_blurring(NULL, 0x00, 0x50, CC1_X, CC1_Y, EBX, EBY);
		imagefilter_blurring(NULL, 0x00, 0x50, CC5_X, CC5_Y, EBX, EBY);
	}
	return;
}