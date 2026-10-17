/*DSA*/#include "fib.h"
uint64_t fibL( int n, uint64_t& prev ) { //线性递归版：入口形式fibL(n, prev)
   if ( 0 == n ) //递归基
      { prev = 1; return 0; } //直接取值：fib(-1) = 1, fib(0) = 0
   else { //否则
      uint64_t prevPrev; prev = fibL( n - 1, prevPrev ); //递归计算前两项
      return prevPrev + prev; //累计
   }
} //用辅助变量记录前一项，返回数列的当前项，O(n)
