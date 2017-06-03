#include <iostream>
#include <queue>
#include <cmath>
#include "Definition.h"

using namespace std;

extern int g_AveWaitTime, g_Time;
static int s_TotCustNum = 0, s_TotWaitTime = 0;

static queue<int> s_CustInLine;

void cust_in(int InNum, int quenum) {
	int i;
	if (quenum == 0) {
		++s_TotCustNum;
		g_AveWaitTime = (int)ceil((double)s_TotWaitTime / s_TotCustNum);
	}
	for (i = 0; i <= InNum - 1; ++i) {
		s_CustInLine.push(g_Time);
	}
	return;
}

void cust_out() {
	++s_TotCustNum;
	s_TotWaitTime += g_Time - s_CustInLine.back();
	s_CustInLine.pop();
	g_AveWaitTime = (int)ceil((double)s_TotWaitTime / s_TotCustNum);
	return;
}
