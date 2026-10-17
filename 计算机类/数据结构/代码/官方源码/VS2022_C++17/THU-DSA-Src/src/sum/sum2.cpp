int sum( int A[], int lo, int hi ) { //入口为sum(A, 0, n)
   if ( hi - lo < 2 ) return A[lo]; //递归基：区间宽度不足2
   int mi = ( lo + hi ) >> 1; //（否则）均分原区间，分别
   return sum( A, lo, mi ) + sum( A, mi, hi ); //递归求和，然后合计
} //数组求和（二分递归版）
