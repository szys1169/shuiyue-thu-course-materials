/*DSA*/ #include "fac.h"

uint64_t facI( int n ) { //阶乘运算（迭代版）
   uint64_t f = 1;
   while ( n > 1 )
      f *= n--;
   return f;
} //facI
