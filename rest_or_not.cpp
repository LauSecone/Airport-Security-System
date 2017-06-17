#include <cstring>
#include "Definition.h"

using namespace std;

static bool s_reststate[MAX_WINDOWS];

void rest_or_not(int &quenum, const string &restrequest) {
	int i, cntrequest = 0;
	double cnt = 0;
	bool requeststore[MAX_WINDOWS] = { 0 };//保存当前时刻最新的安检口休息申请
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (g_windows[i].State != RESTTING_PORT && g_windows[i].State != CLOSE_PORT && restrequest[i] == 'R')
			requeststore[i] = 1;
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (g_windows[i].State != RESTTING_PORT && g_windows[i].State != CLOSE_PORT && g_windows[i].RestSignal != 1)
			++cnt;//统计正常工作的安检口个数
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (s_reststate[i] || requeststore[i])//考虑到安检口重复申请休息
			++cntrequest;//统计休息申请个数
	while (cnt > 1 && quenum / cnt < g_MaxSeqLen && cntrequest > 0) {
		int flag = 1;
		for (i = 1; i <= REAL_WINDOWS && flag; ++i)
			if (s_reststate[i]) {
				flag = 0;//确保一次循环只会允许一个安检口休息
				s_reststate[i] = 0;
				requeststore[i] = 0;//考虑到安检口重复申请休息
				g_windows[i].RestSignal = 1;
				--cnt;
			}//对优先的部分安检口进行判定
		if (flag) {
			int sec_flag = 1, minrest = 2100000000;
			for (i = 1; i <= REAL_WINDOWS; ++i)
				if (requeststore[i] && g_windows[i].TotOffTime < minrest)
					minrest = g_windows[i].TotOffTime;
			for (i = 1; i <= REAL_WINDOWS && sec_flag; ++i) {
				if (requeststore[i] && g_windows[i].TotOffTime == minrest) {
					g_windows[i].RestSignal = 1;
					requeststore[i] = 0;
					sec_flag = 0;//确保一次循环只会允许一个安检口休息
					--cnt;
				}
			}
		}
		--cntrequest;
	}
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (requeststore[i])
			s_reststate[i] = 1;//保存未被批准的休息申请	
}

int rest_state(int num) {
	return s_reststate[num];
}