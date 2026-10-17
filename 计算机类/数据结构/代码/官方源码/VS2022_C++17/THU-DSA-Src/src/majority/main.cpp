#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "_share/util.h"
#include "UniPrint/print.h"
#include "vector/vector.h"
#include "majority.h"
#include "majorityCandidate.h"
#include "majorityCheck.h"

int main( int argc, char* argv[] ) { //众数算法测试
   if ( 2 > argc ) { printf( "Usage: %s <n>\a\a\n", argv[0] ); return 1; }
   Rank n = atoi( argv[1] );
   if ( n < 1 ) { printf( "Invalid arguments\a\a\n" ); return 1; }
   srand( (uint32_t) time(nullptr) );
//随机生成向量
   Vector<int> A; //以整型为例
   int maj = rand() % n; printf( "%d is highly possible to be a majority\n", maj ); //随机确定一个maj候选
   while ( A.size() < n ) { //继续不断插入n，直至共有n个元素
      int ele = ( rand() % 100 < 50 ) ? maj : rand() % n; //49%的概率确定是maj，51%随机（可实验不同概率的效果）
      A.insert( A.size(), ele );
   }
   print( A ); //均匀随机置乱
//计算众数
   majority( A, maj ) ?
   printf( "Majority element found as %d\n", maj ) :
   printf( "Majority element NOT found\n" );
//通过排序进一步验证
   A.sort(); print( A );
//返回
   return 0;
}
