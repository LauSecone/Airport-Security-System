#include <cstring>
#include "Definition.h"

using namespace std;

void cust_in(int ,int );

void come_in_cust(int &quenum, int custnum) {
	if (quenum + custnum < g_MaxCustSingleLine * g_MaxLines){
		cust_in(custnum,quenum);//�˿ͽ��뻺�������ź�
		quenum += custnum;
	}
	else{
		cust_in(g_MaxCustSingleLine * g_MaxLines - quenum,quenum);//�˿ͽ��뻺�������ź�
		quenum = g_MaxCustSingleLine * g_MaxLines;//�Ŷӻ������޷�����ȫ�����³˿�
	}
}
