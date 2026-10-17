#pragma once

#include<iostream>
using namespace std;

#include "_share/util.h"
#include "UniPrint/print.h"

#include "Queue/Queue.h"

void qWinSum( Queue<int>&, Rank, Rank ); //计算序列的滑动窗口和
void qPreSum( Queue<int>&, Rank ); // 计算序列的前缀和
