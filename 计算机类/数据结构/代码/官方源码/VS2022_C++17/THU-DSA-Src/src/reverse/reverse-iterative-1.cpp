/*DSA*/#include "_share/util.h"
/*DSA*/#include "UniPrint/print_int_array.h"

void reverse( int* A, int n ) { //数组倒置（规范整理之后的迭代版）
   while ( 1 < n ) { //用while替换跳转标志和if，完全等效
      swap( A[0], A[n-1] ); //交换首元素和末元素
      A++; n -= 2; //收缩待倒置区间
   }
} //O(n)时间 + O(1)空间
