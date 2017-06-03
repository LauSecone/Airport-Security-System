#include <cstring>
#include "Definition.h"

using namespace std;

void cust_out();

void allo_cust(int &quenum,const string &CloseRequest) {
	int i, custtotal = 0, custneed = 0;
	bool winstate[MAX_WINDOWS] = { 0 };
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (g_windows[i].State != RESTTING_PORT && g_windows[i].State != CLOSE_PORT && CloseRequest[i] != 'X')
		{
			winstate[i] = 1;
			custtotal += g_windows[i].CurNum;//Õ≥º∆∞≤ºÏø⁄≥ÀøÕ◊‹ �?
			custneed += g_MaxSeqLen;//Õ≥º∆∞≤ºÏø⁄ÃÓ¬˙À˘–Ë≥ÀøÕ ˝ 
		}
	while (custtotal < custneed && quenum > 0) {
		int mincust = 2100000000, dest;
		double maxeffi = -1;
		for (i = 1; i <= REAL_WINDOWS; ++i)
			if (winstate[i] && g_windows[i].CurNum < mincust)
				mincust = g_windows[i].CurNum;
		for (i = 1; i <= REAL_WINDOWS; ++i)
			if (winstate[i] && g_windows[i].CurNum == mincust)
			{
				double efficiency = (double)g_windows[i].TotNum / (g_windows[i].TotServeTime + 1);
				if (efficiency > maxeffi)
				{
					maxeffi = efficiency;
					dest = i;
				}
			}
		++g_windows[dest].CurNum;
		cust_out();
		++custtotal;
		--quenum;
	}
}
