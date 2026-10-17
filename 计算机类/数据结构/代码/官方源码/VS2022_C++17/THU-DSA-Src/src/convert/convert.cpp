/*DSA*/#include "convert.h"
/*DSA*/
void convert( uint64_t n, int base ) { //进制转换（迭代版）
   const char digit[] = "0123456789ABCDEF"; //仅测试16以内的进制，如有必要可自行扩充
   Stack<char> S; //代替调用栈
   while ( 0 < n ) { //由低到高，逐一算出各数位
      S.push( digit[ n % base ] ); //模余（当前位）入栈
      n /= base; //n更新为除商
   }
   while ( !S.empty() ) //按常规次序
      output( S.pop() ); //输出各数位（具体方式可自定义）
} //时间、空间均为O(logn)，但常系数相对于递归版更小
