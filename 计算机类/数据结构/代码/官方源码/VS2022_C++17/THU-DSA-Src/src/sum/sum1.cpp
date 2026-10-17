int sum( int A[], int n ) {
   if ( 1 > n ) //递归基
      return 0; //直接计算
   else //一般情况：递归汇总前n-1项，再累计末项
      return sum( A, n - 1 ) + A[n - 1];
} //数组求和（线性递归版）
