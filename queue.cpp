#include <cstring>
#include "Definition.h"

using namespace std;

static bool winstate[10], reststate[10];

void Allocust(int*quenum, int maxseqlen) {
	int i, custtotal = 0, custneed = 0;
	memset(winstate, 0, sizeof(winstate));
	for (i = 1; i <= MAX_WINDOWS; i++)
		if (windows[i].State != 4 && windows[i].State != 5)
		{
			winstate[i] = 1;
			custtotal += windows[i].CurNum;//ͳ�ư���ڳ˿����� 
			custneed += maxseqlen;//ͳ�ư������������˿��� 
		}
	while (custtotal < custneed && quenum > 0) {
		int mincust = 2100000000, dest;
		double maxeffi = 0;
		for (i = 1; i <= MAX_WINDOWS; i++)
			if (winstate[i] && windows[i].CurNum < mincust)
				mincust = windows[i].CurNum;
		for (i = 1; i <= MAX_WINDOWS; i++)
			if (winstate[i] && windows[i].CurNum == mincust)
			{
				double efficiency = (double)windows[i].TotServeTime / windows[i].TotNum;
				if (efficiency > maxeffi)
				{
					maxeffi = efficiency;
					dest = i;
				}
				windows[dest].CurNum++;
				custtotal++;
				(*quenum)--;
			}
	}
}

void Comeincust(int *quenum, int custnum, int maxcustsingleline, int maxlines) {
	if ((*quenum) + custnum < maxcustsingleline * maxlines)
		(*quenum) += custnum;
	else
		(*quenum) = maxcustsingleline * maxlines;//�Ŷӻ������޷�����ȫ�����³˿�    
}

void Restornot(int *quenum, string restrequest, int maxseqlen) {
	int i, flag = 0, minrest = 2100000000;
	double cnt = 0;
	for (i = 1; i <= MAX_WINDOWS; i++)
		if (windows[i].State != 4 && windows[i].State != 5)
			cnt++;
	for (i = 1; i <= MAX_WINDOWS; i++)
		if (reststate[i] && (*quenum) / cnt < maxseqlen && flag == 0) {
			windows[i].RestSignal = 1;
			reststate[i] = 0;
			flag = 1;//����ֻ��һ������ڿ���������Ϣ 
		}//�ж�����δ����׼�İ�����Ƿ����������Ϣ 
	if (flag) {
		for (i = 1; i <= MAX_WINDOWS; i++)
			if (restrequest[i] == 'R')
				reststate[i] = 1;
	}
	else {
		for (i = 1; i <= MAX_WINDOWS; i++)
			if ((restrequest[i] == 'R' || reststate[i]) && windows[i].TotOffTime < minrest)
				minrest = windows[i].TotOffTime;
		for (i = 1; i <= MAX_WINDOWS; i++) {
			if ((restrequest[i] == 'R' || reststate[i]) && windows[i].TotOffTime == minrest) {
				windows[i].RestSignal = 1;
				reststate[i] = 0;
			}
			if ((restrequest[i] == 'R' || reststate[i]) && windows[i].TotOffTime != minrest)
				reststate[i] = 1;
		}
	}
}
