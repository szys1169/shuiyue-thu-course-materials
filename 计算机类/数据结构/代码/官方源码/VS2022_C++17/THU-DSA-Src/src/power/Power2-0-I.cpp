/*DSA*/#include <typeinfo>

uint64_t power2BF_I( int n ) { //幂函数2^n算法（蛮力迭代版），n >= 0
   uint64_t pow = 1; //O(1)：累积器初始化为2^0
   while ( 0 < n -- ) //O(n)：迭代n轮，每轮都
      pow <<= 1; //O(1)：将累积器翻倍
   return pow; //O(1)：返回累积器
} //O(n) = O(2^r)，r为输入指数n的比特位数
