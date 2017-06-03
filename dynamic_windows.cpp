#include "Definition.h"

using namespace std;

void dynamic_windows(const int queuenum,string &CloseRequest){
    int OpenWindows = 0,i,j,NeedWindows = 0;
    for (i = 1;i <= 4;++i){
        for (j = 1;j <= REAL_WINDOWS; ++j){
            if (g_windows[j].State != CLOSE_PORT){
                ++OpenWindows;
            }
        }
        if (queuenum >= OpenWindows * 3){
            ++NeedWindows;
        }
    }
    for (i=5;i<=REAL_WINDOWS;++i){
        g_windows[i].State = CLOSE_PORT;
        CloseRequest[i] = 'X';
    }
    for (i=5;i<=NeedWindows+4;++i){
        if(g_windows[i].State == CLOSE_PORT){
            g_windows[i].State = 1;
        }
        if(CloseRequest[i] == 'X'){
         CloseRequest[i] = '0';
        }
    }
}
