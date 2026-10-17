int sumI( int A[], int n ) {
   int sum = 0; //累计器
   for ( int i = 0; i < n; i++ )
      sum += A[i]; //逐项累计
   return sum; //返回累计值
} //数组求和（迭代版）
