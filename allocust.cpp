#include <cstring>
#include "Definition.h"

using namespace std;

void allocust(int*quenum) {
	int i, custtotal = 0, custneed = 0;
	bool winstate[10] = {0};
	for (i = 1; i <= MAX_WINDOWS; i++)
		if (windows[i].State != 4 && windows[i].State != 5)
		{
			winstate[i] = 1;
			custtotal += windows[i].CurNum;//统计安检口乘客总数 
			custneed += MaxSeqLen;//统计安检口填满所需乘客数 
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
