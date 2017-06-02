#include <cstring>
#include "Definition.h"

using namespace std;

static bool s_reststate[MAX_WINDOWS];

void rest_or_not(int &quenum, const string &restrequest) {
	int i, cntrequest = 0;
	double cnt = 0;
	bool requeststore[MAX_WINDOWS] = { 0 };
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (restrequest[i] == 'R')
			requeststore[i] = 1;
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (g_windows[i].State != RESTTING_PORT && g_windows[i].State != CLOSE_PORT)
			++cnt;
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (s_reststate[i] || requeststore[i])
			++cntrequest;
	while (cnt >= 1 && quenum / cnt < g_MaxSeqLen && cntrequest > 0) {
		int flag = 1;
		for (i = 1; i <= REAL_WINDOWS && flag; ++i)
			if (s_reststate[i]) {
				flag = 0;
				s_reststate[i] = 0;
				requeststore[i] = 0;
				g_windows[i].RestSignal = 1;
				--cnt;
			}
		if (flag) {
			int sec_flag = 1, minrest = 2100000000;
			for (i = 1; i <= REAL_WINDOWS; ++i)
				if (requeststore[i] && g_windows[i].TotOffTime < minrest)
					minrest = g_windows[i].TotOffTime;
			for (i = 1; i <= REAL_WINDOWS && sec_flag; ++i) {
				if (requeststore[i] && g_windows[i].TotOffTime == minrest) {
					g_windows[i].RestSignal = 1;
					requeststore[i] = 0;
					sec_flag = 0;
					--cnt;
				}
			}
		}
		--cntrequest;
	}
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (requeststore[i])
			s_reststate[i] = 1;
}
