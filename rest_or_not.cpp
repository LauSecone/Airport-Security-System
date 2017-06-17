#include <cstring>
#include "Definition.h"

using namespace std;

static bool s_reststate[MAX_WINDOWS];

void rest_or_not(int &quenum, const string &restrequest) {
	int i, cntrequest = 0;
	double cnt = 0;
	bool requeststore[MAX_WINDOWS] = { 0 };//���浱ǰʱ�����µİ������Ϣ����
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (g_windows[i].State != RESTTING_PORT && g_windows[i].State != CLOSE_PORT && restrequest[i] == 'R')
			requeststore[i] = 1;
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (g_windows[i].State != RESTTING_PORT && g_windows[i].State != CLOSE_PORT && g_windows[i].RestSignal != 1)
			++cnt;//ͳ�����������İ���ڸ���
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (s_reststate[i] || requeststore[i])//���ǵ�������ظ�������Ϣ
			++cntrequest;//ͳ����Ϣ�������
	while (cnt > 1 && quenum / cnt < g_MaxSeqLen && cntrequest > 0) {
		int flag = 1;
		for (i = 1; i <= REAL_WINDOWS && flag; ++i)
			if (s_reststate[i]) {
				flag = 0;//ȷ��һ��ѭ��ֻ������һ���������Ϣ
				s_reststate[i] = 0;
				requeststore[i] = 0;//���ǵ�������ظ�������Ϣ
				g_windows[i].RestSignal = 1;
				--cnt;
			}//�����ȵĲ��ְ���ڽ����ж�
		if (flag) {
			int sec_flag = 1, minrest = 2100000000;
			for (i = 1; i <= REAL_WINDOWS; ++i)
				if (requeststore[i] && g_windows[i].TotOffTime < minrest)
					minrest = g_windows[i].TotOffTime;
			for (i = 1; i <= REAL_WINDOWS && sec_flag; ++i) {
				if (requeststore[i] && g_windows[i].TotOffTime == minrest) {
					g_windows[i].RestSignal = 1;
					requeststore[i] = 0;
					sec_flag = 0;//ȷ��һ��ѭ��ֻ������һ���������Ϣ
					--cnt;
				}
			}
		}
		--cntrequest;
	}
	for (i = 1; i <= REAL_WINDOWS; ++i)
		if (requeststore[i])
			s_reststate[i] = 1;//����δ����׼����Ϣ����	
}

int rest_state(int num) {
	return s_reststate[num];
}