#include <cstring>
#include "Definition.h"

using namespace std;

static bool reststate[REAL_WINDOWS];

void restornot(int &quenum, const string &restrequest) {
	int i, cntrequest = 0;
	double cnt = 0;
	bool requeststore[REAL_WINDOWS] = { 0 };
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (restrequest[i] == 'R')
			requeststore[i] = 1;
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (windows[i].State != RESTTING_PORT && windows[i].State != CLOSE_PORT)
			++cnt;
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (reststate[i] || requeststore[i])
			++cntrequest;
	while (cnt >= 1 && quenum / cnt < MaxSeqLen && cntrequest > 0) {
		int flag = 1;
		for (i = 1; i <= REAL_WINDOWS && flag; ++i)
			if (reststate[i]) {
				flag = 0;
				reststate[i] = 0;
				requeststore[i] = 0;
				windows[i].RestSignal = 1;
				--cnt;
			}
		if (flag) {
			int sec_flag = 1, minrest = 2100000000;
			for (i = 1; i <= REAL_WINDOWS; ++i)
				if (requeststore[i] && windows[i].TotOffTime < minrest)
					minrest = windows[i].TotOffTime;
			for (i = 1; i <= REAL_WINDOWS && sec_flag; ++i) {
				if (requeststore[i] && windows[i].TotOffTime == minrest) {
					windows[i].RestSignal = 1;
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
			reststate[i] = 1;
}
