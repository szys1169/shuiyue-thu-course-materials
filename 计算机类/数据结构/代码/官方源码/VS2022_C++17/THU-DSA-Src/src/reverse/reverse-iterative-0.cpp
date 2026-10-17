/*DSA*/#include "_share/util.h"
/*DSA*/#include "UniPrint/print_int_array.h"

void reverse( int * A, int n ) { //数组倒置（直接改造而得的迭代版）
next: //算法起始位置添加跳转标志
   if ( n < 2 ) return;
   swap( A[0], A[n-1] ); //交换首元素和末元素
   A++; n -= 2; //收缩待倒置区间
   goto next; //跳转至算法体的起始位置，迭代地倒置中缀
} //O(n)时间 + O(1)空间
