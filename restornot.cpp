#include <cstring>
#include "Definition.h"

using namespace std;

static bool reststate[10];

void restornot(int *quenum, string restrequest) {
	int i, flag = 0, minrest = 2100000000;
	double cnt = 0;
	for (i = 1; i <= REAL_WINDOWS; i++)
		if (windows[i].State != 4 && windows[i].State != 5)
			cnt++;
	for (i = 1; i <= REAL_WINDOWS; i++)
		if (reststate[i] && (*quenum) / cnt < MaxSeqLen && flag == 0) {
			windows[i].RestSignal = 1;
			reststate[i] = 0;
			flag = 1;//限制只有一个安检口可以优先休息 
		}//判断申请未被批准的安检口是否可以优先休息 
	if (flag) {
		for (i = 1; i <= REAL_WINDOWS; i++)
			if (restrequest[i] == 'R')
				reststate[i] = 1;
	}
	else {
		for (i = 1; i <= REAL_WINDOWS; i++)
			if ((restrequest[i] == 'R' || reststate[i]) && windows[i].TotOffTime < minrest)
				minrest = windows[i].TotOffTime;
		for (i = 1; i <= REAL_WINDOWS; i++) {
			if ((restrequest[i] == 'R' || reststate[i]) && windows[i].TotOffTime == minrest) {
				windows[i].RestSignal = 1;
				reststate[i] = 0;
			}
			if ((restrequest[i] == 'R' || reststate[i]) && windows[i].TotOffTime != minrest)
				reststate[i] = 1;
		}
	}
}
