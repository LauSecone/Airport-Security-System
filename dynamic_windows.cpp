#include "Definition.h"

using namespace std;

void dynamic_windows(const int queuenum,string &CloseRequest){
    int OpenWindows = 0,NeedWindows = 0;
    int i,j;
    for (j = 1;j <= REAL_WINDOWS; j++){
        if (g_windows[j].State != CLOSE_PORT){
            ++OpenWindows;
        }
    }
    for (i = 1;i <= 4;i++){
        if (queuenum >= OpenWindows * 3 && OpenWindows <= 8){
            ++OpenWindows;
            ++NeedWindows;
        }
    }
    for (i = 1;i <= 4;i++){
        if (queuenum < OpenWindows * 2 && OpenWindows >= 4){
            --OpenWindows;
        }
        NeedWindows = OpenWindows - 4 ;
    }
    for (i=5;i<=REAL_WINDOWS;i++){
        if(g_windows[i].CurNum != 0){
            CloseRequest[i] = 'X';
        }
        if(g_windows[i].State == AVAILABLE_PORT){
            g_windows[i].State = CLOSE_PORT;
        }
    }
    for (i=5;i<= NeedWindows + 4;i++){
        if(g_windows[i].State == CLOSE_PORT){
            g_windows[i].State = AVAILABLE_PORT;
        }
        if(CloseRequest[i] == 'X'){
            CloseRequest[i] = '0';
        }
    }
}
