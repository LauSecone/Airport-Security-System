#include "Definition.h"

using namespace std;

void check_quit(int &State) {
	//���ϰ�״̬���Ƴ�
	if (State == ON_DUTY) {
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
		State = OFF_DUTY;
	}
	return;
}
