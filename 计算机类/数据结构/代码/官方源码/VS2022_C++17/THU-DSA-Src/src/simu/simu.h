#pragma once
#pragma warning(disable : 4996)

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>

#include "_share/util.h"
#include "UniPrint/print.h"

#include "Queue/Queue.h"

int bestWindow( Queue<int> *, int );
void printCustomer( int );
void displayProgress( Queue<int>*, int, int );
void simu( int, int );

extern int delay; //控制进度显示的延迟
