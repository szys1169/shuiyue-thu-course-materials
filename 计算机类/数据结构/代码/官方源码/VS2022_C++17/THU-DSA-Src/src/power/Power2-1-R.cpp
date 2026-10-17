/*DSA*/ #include<typeinfo>

inline uint64_t sqr( uint64_t a ) { return a* a; } //平方：若是连续执行，很快就会数值溢出！
uint64_t power2( int n ) { //幂函数2^n算法（优化递归版），n >= 0
   if ( 0 == n ) return 1; //递归基；否则，视n的奇偶分别递归
   return( n&1 ) ? sqr( power2( n >> 1 ) ) << 1 : sqr( power2( n >> 1 ) );
} //O(logn) = O(r)，r为输入指数n的比特位数
