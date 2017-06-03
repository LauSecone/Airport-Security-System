#include <cstring>
#include "Definition.h"

using namespace std;

void cust_out();

void allo_cust(int &quenum,const string &CloseRequest) {
	int i, custtotal = 0, custneed = 0;
	bool winstate[MAX_WINDOWS] = { 0 };//存储安检口的具体状态 
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (g_windows[i].State != RESTTING_PORT && g_windows[i].State != CLOSE_PORT && CloseRequest[i] != 'X')
		{
			winstate[i] = 1;//统计安检口状态
			custtotal += g_windows[i].CurNum;//统计安检口乘客总数
			custneed += g_MaxSeqLen;//统计安检口填满所需乘客数 
		}
	while (custtotal < custneed && quenum > 0) {
		int mincust = 2100000000, dest;
		double maxeffi = -1;
		for (i = 1; i <= REAL_WINDOWS; ++i)
			if (winstate[i] && g_windows[i].CurNum < mincust)
				mincust = g_windows[i].CurNum;//比较出安检口乘客数最小值	
		for (i = 1; i <= REAL_WINDOWS; ++i)
			if (winstate[i] && g_windows[i].CurNum == mincust)
			{
				double efficiency = (double)g_windows[i].TotNum / (g_windows[i].TotServeTime + 1);
				if (efficiency > maxeffi)
				{
					maxeffi = efficiency;
					dest = i;
				}//效率仍然相同时取编号小的安检口
			}//比较出安检口乘客数最少的安检口中效率最高的安检口
		++g_windows[dest].CurNum;
		cust_out();//乘客出缓冲区的信号
		++custtotal;
		--quenum;
		//分配乘客的具体操作
	}
}
