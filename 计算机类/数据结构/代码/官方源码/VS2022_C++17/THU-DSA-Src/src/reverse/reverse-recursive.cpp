/*DSA*/#include "_share/util.h"
/*DSA*/#include "UniPrint/print_int_array.h"

void reverse( int* A, int n ) {
   if ( n < 2 ) return; //递归基：两种情况
   swap( A[0], A[n-1] ); //交换首元素和末元素
   reverse( A + 1, n - 2 ); //递归倒置中缀
} //数组倒置（递归版）：O(n)时间 + O(n)空间
