#include <iostream>
#include <queue>
#include <cmath>
#include "Definition.h"

using namespace std;

extern int AveWaitTime, Time;
static int TotCustNum = 0, TotWaitTime = 0;

static queue<int> CustInLine;

void cust_in(int InNum) {
	int i;
	for (i = 0; i <= InNum - 1; ++i) {
		CustInLine.push(Time);
	}
	return;
}

void cust_out() {
	++TotCustNum;
	TotWaitTime += Time -CustInLine.back();
	CustInLine.pop();
	AveWaitTime = ceil((double)TotWaitTime / TotCustNum);
	return;
}
