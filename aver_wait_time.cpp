#include <queue>
#include <cmath>
#include "Definition.h"

using namespace std;

extern int g_AveWaitTime, g_Time;
static int s_TotCustNum = 0, s_TotWaitTime = 0;

static queue<int> s_CustInLine;

void cust_in(int InNum, int quenum) {
	int i;
	//减少以前数据的影响
	if (quenum == 0) {
		++s_TotCustNum;
		g_AveWaitTime = (int)ceil((double)s_TotWaitTime / s_TotCustNum);
	}
	//让InNum人数进栈
	for (i = 0; i <= InNum - 1; ++i) {
		s_CustInLine.push(g_Time);
	}
	return;
}

void cust_out() {
	//统计人数
	++s_TotCustNum;
	//出栈，统计时间
	s_TotWaitTime += g_Time - s_CustInLine.front();
	s_CustInLine.pop();
	//计算期望等待时间
	g_AveWaitTime = (int)ceil((double)s_TotWaitTime / s_TotCustNum);
	return;
}
