/*DSA*/#include "convert/convert.h"
/*DSA*/
void convert( uint64_t n, int base ) { //进制转换（递归版）
   static const char digit[] = "0123456789ABCDEF"; //数位符号，如有必要可相应扩充
   if ( n < 1 ) return; //递归基
   convert( n / base, base ); //头递归：先输出所有的高位
   output( digit[n % base] ); //再输出最低位（具体方式可自定义）
} //时间、空间均为O(logn)，但常系数相对于迭代版更大
