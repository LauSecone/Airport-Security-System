#include "Definition.h"

using namespace std;

extern int g_state;

void check_quit() {
	//���ϰ�״̬���Ƴ�
	if (g_state == ON_DUTY) {
		return;
	}
	//���д��ھ����ˣ��°�
	int flag = 1;
	for (int i = 1; i <= 8; ++i) {
		if (g_windows[i].CurNum != 0) {
			flag = 0;
		}
	}
	if (flag) {
		g_state = OFF_DUTY;
	}
	return;
}
