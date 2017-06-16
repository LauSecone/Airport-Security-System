#pragma once
#ifndef DEFINITION_H_
#define DEFINITION_H_

#include <string>

//Windows Number
#define MAX_WINDOWS 10
#define INIT_OPEN_WINDOWS 4
#define REAL_WINDOWS 8

//Syatem State
#define OFF_DUTY 0
#define ON_DUTY 1
#define WAIT_FOR_QUIT 2

//Windows State
#define AVAILABLE_PORT 1
#define CHECKING_PORT 2
#define SWITCHING_PORT 3
#define RESTTING_PORT 4
#define CLOSE_PORT 5

//Input and Output Method
#define READ_VIA_FILE 0
#define READ_VIA_KEYBOARD 1
#define CREAT_VIA_POISSON 2
#define READ_USE_THREAD 3
#define READ_VIA_SCREEN 4
#define READ_VIA_GRAPH 5
#define WRITE_VIA_FILE 0
#define WRITE_VIA_MONITOR 1

//Size of Screen
#define SCREEN_X 1280
#define SCREEN_Y 720

struct WindowsPort {
	int State;
	int CurNum, CurCustTime;
	int CurStateTime;
	int TotOffTime, TotOnTime;
	int TotServeTime, TotNum, ScheRestTime, RestSignal, TotRestTime;
};

extern int g_MaxCustSingleLine, g_MaxLines, g_MaxSeqLen, g_MinTimeLen, g_MaxTimeLen, g_MinRestSec, g_MaxRestSec;
extern struct WindowsPort g_windows[MAX_WINDOWS];

#endif
//DEFINITION_H_