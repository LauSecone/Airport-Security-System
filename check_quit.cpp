#include "Definition.h"

using namespace std;

void check_quit(int &State) {
	//若上班状态，推出
	if (State == ON_DUTY) {
		return;
	}
	//所有窗口均无人，下班
	int flag = 1;
	for (int i = 1; i <= 8; ++i) {
		if (g_windows[i].CurNum != 0) {
			flag = 0;
		}
	}
	if (flag) {
		State = OFF_DUTY;
	}
	return;
}
