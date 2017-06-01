#include <cstring>
#include "Definition.h"

using namespace std;

void allocust(int &quenum) {
	int i, custtotal = 0, custneed = 0;
	bool winstate[10] = {0};
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (windows[i].State != RESTTING_PORT && windows[i].State != CLOSE_PORT)
		{
			winstate[i] = 1;
			custtotal += windows[i].CurNum;//统计安检口乘客总数 
			custneed += MaxSeqLen;//统计安检口填满所需乘客数 
		}
	while (custtotal < custneed && quenum > 0) {
		int mincust = 2100000000, dest;
		double maxeffi = -1;
		for (i = 1; i <= REAL_WINDOWS; ++i)
			if (winstate[i] && windows[i].CurNum < mincust)
		  		mincust = windows[i].CurNum;
		for (i = 1; i <= REAL_WINDOWS; ++i)
			if (winstate[i] && windows[i].CurNum == mincust)
			{
				double efficiency = (double)windows[i].TotNum /(windows[i].TotServeTime + 1);
				if (efficiency > maxeffi)
				{
					maxeffi = efficiency;
					dest = i;
				}
			}
		++windows[dest].CurNum;
		++custtotal;
		--quenum;
	}
}
