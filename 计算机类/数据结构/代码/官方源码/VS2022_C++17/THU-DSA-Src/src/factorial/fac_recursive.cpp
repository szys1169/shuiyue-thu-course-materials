/*DSA*/ #include "fac.h"

uint64_t facR( int n ) { //阶乘运算（递归版）
   return ( n < 1 ) ? 1 : n * facR( n - 1 );
} //facR
