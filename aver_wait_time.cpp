#include <iostream>
#include <queue>
#include "Definition.h"

using namespace std;
extern int Time;

int AveWaitTime = 0, TotCustNum = 0, TotWaitTime = 0;

queue<int> CustInLine;

void cust_in(int InNum){
    int i;
    for(i=0;i<=InNum-1;++i){
        CustInLine.push(Time);
    }
    return;
}

void cust_out(){
    while(!CustInLine.empty()){
        ++TotCustNum;
        TotWaitTime += CustInLine.back();
        CustInLine.pop();
        AveWaitTime = TotWaitTime / TotCustNum;
    }
    return;
}
