/*DSA*/#include "string_pm/string_pm_test.h"

int match( char* P, char* T ) { //Boyer-Morre算法（完全版，兼顾Bad Character与Good Suffix）
   int* bc = buildBC( P ); int* gs = buildGS( P ); //构造BC表和GS表
   int n = strlen( T ), i = 0;
   int m = strlen( P ), j = m-1;
   while ( (0 <= j) && (i <= n-m) ) //自右向左逐个比对字符
      /*DSA*/{showProgress( T, P, i, j );
      if (T[i + j] == P[j]) //若匹配
         j--; //则转到下一对字符
      else //否则
         { i += max(gs[j], j - bc[T[i+j]]); j = m-1; } //借助BC表快速右移模式串
      /*DSA*/}
   /*DSA*/if (i > n-m) showProgress( T, P, i, j ); //last failure
   delete [] gs; delete [] bc; return i; //销毁GS表和BC表，返回最终的对齐位置
}
