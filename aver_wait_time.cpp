#include <iostream>
#include <queue>
#include <cmath>
#include "Definition.h"

using namespace std;

extern int g_AveWaitTime, g_Time;
static int s_TotCustNum = 0, s_TotWaitTime = 0;

static queue<int> s_CustInLine;

void cust_in(int InNum,int quenum) {
	int i;
	if (quenum == 0) {//若排队区无人（乘客不需排队）
		++s_TotCustNum;
		g_AveWaitTime = ceil((double)s_TotWaitTime / s_TotCustNum);
	}
	for (i = 0; i <= InNum - 1; ++i) {//需要排队
		s_CustInLine.push(g_Time);
	}
	return;
}

void cust_out() {//计算平均时间
	++s_TotCustNum;
	s_TotWaitTime += g_Time - s_CustInLine.back();
	s_CustInLine.pop();
	g_AveWaitTime = ceil((double)s_TotWaitTime / s_TotCustNum);
	return;
}
