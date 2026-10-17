#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

#include "_share/util.h"
#include "UniPrint/print.h"

#include "huffman_PQ.h"

extern uint32_t* stat( char* ); //根据样本文件统计各字符出现频率
extern HuffForest initForest( uint32_t* ); //创建编码树森林
extern HuffTree huffTree( HuffForest& ); //构造编码树
extern HuffTable huffCodeTable( HuffTree& ); //由编码树转换为编码表
extern int encode( HuffTable&, Bitmap&, char* ); //明文的编码，返回编码长度
extern void decode( HuffTree&, Bitmap&, int ); //二进制串的解码

struct visit { virtual void operator() ( HuffChar& e ) { printf( "%8d", e.weight ); } };
template <typename T, typename V> void levelorder( BNP<T>, V& );
