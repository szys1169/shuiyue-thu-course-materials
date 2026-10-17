/*DSA*/ #include "fib.h"
extern uint64_t M[]; // 快查表：已初始化为全0
uint64_t fibM( int n ) { //记忆化版：O(n)
   if ( n < 2 ) return n; //递归基
   if ( ! M[n] ) //若尚未算出，则照常递归求值
      M[n] = fibM( n - 1 ) + fibM( n - 2 );
   return M[n];
} //fibM
