#include <cstring>
#include "Definition.h"

using namespace std;

void cust_in(int ,int );

void come_in_cust(int &quenum, int custnum) {
	if (quenum + custnum < g_MaxCustSingleLine * g_MaxLines){
		cust_in(custnum,quenum);
		quenum += custnum;
	}
	else{
		cust_in(g_MaxCustSingleLine * g_MaxLines - quenum,quenum);
		quenum = g_MaxCustSingleLine * g_MaxLines;//排队缓冲区无法容纳全部的新乘客
	}
}
