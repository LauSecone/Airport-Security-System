#include <cstring>
#include "Definition.h"

using namespace std;

void comeincust(int *quenum, int custnum) {
	if ((*quenum) + custnum < MaxCustSingleLine * MaxLines)
		(*quenum) += custnum;
	else
		(*quenum) = MaxCustSingleLine * MaxLines;//�Ŷӻ������޷�����ȫ�����³˿�    
}
