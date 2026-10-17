/*DSA*/#include "string_pm/string_pm_test.h"

int* buildNext( char* P ) { //构造模式串P的next表
   int m = strlen( P ), j = 0; //“主”串指针
   int* next = new int[m]; int t = next[0] = -1; //next表，首项必为-1
   while ( j < m - 1 )
      if ( 0 > t || P[t] == P[j] ) { //匹配
         ++t; ++j; next[j] = t; //则递增赋值：此处可改进...
      } else //否则
         t = next[t]; //继续尝试下一值得尝试的位置
   /*DSA*/printString( P ); printf( "\n" );
   /*DSA*/printNext( next, 0, m );
   return next;
}
