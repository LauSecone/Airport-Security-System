#pragma once
#ifndef DEFINITION_H
#define DEFINITION_H

#include <iostream>
#include <fstream>
#include <string>
#define MAX_WINDOWS 10
#define OFF_DUTY 0
#define ON_DUTY 1
#define WAIT_FOR_QUIT 2

struct WindowsPort {
	int State;
	int CurNum, CurCustTime;
	int CurStateTime;
	int TotOffTime, TotOnTime;
	int TotServeTime, TotNum, ScheRestTime, RestSignal;
};

extern int MaxCustSingleLine, MaxLines, MaxSeqLen, MinTimeLen, MaxTimeLen, MinRestSec, MaxRestSec;
extern struct WindowsPort windows[MAX_WINDOWS];

#endif