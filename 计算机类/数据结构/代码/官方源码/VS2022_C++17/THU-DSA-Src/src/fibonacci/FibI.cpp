/*DSA*/#include "fib.h"
uint64_t fibI( int n ) { //迭代版：O(n)
   uint64_t f = 1, g = 0; //初始化：fib(-1)、fib(0)
   while ( 0 < n-- ) { //由定义，经n次加法、减法计算fib(n)
      g += f;
      f = g - f;
   }
   return g; //返回
} //fibI
