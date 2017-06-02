#include <cstring>
#include "Definition.h"

using namespace std;
void cust_in(int );

void comeincust(int &quenum, int custnum) {
	if (quenum + custnum < MaxCustSingleLine * MaxLines){
		cust_in(custnum);
		quenum += custnum;
	}
	else{
		cust_in(MaxCustSingleLine * MaxLines - quenum);
		quenum = MaxCustSingleLine * MaxLines;//排队缓冲区无法容纳全部的新乘客
	}
}
