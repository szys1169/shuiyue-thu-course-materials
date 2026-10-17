/*DSA*/#include <typeinfo>

uint64_t power2BF( int n ) { //幂函数2^n算法（蛮力递归版），n >= 0
   return( 1 > n ) ? 1 : power2BF( n - 1 ) << 1; //递归
} //O(n) = O(2^r)，r为输入指数n的比特位数
