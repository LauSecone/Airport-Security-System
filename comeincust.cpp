#include <cstring>
#include "Definition.h"

using namespace std;

void comeincust(int &quenum, int custnum) {
	if (quenum + custnum < MaxCustSingleLine * MaxLines)
		quenum += custnum;
	else
		quenum = MaxCustSingleLine * MaxLines;//排队缓冲区无法容纳全部的新乘客    
}
