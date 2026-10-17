/*DSA*/#include "fib.h"
uint64_t fib( int n ) { //二分递归版：O(2^n)
   if ( n < 2 ) return n; //递归基
   return fib( n - 1 ) + fib( n - 2 );
} //fib
