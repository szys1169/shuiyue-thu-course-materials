int maxI( int A[], int n ) { //求数组最大值算法（迭代版）
   int m = INT_MIN; //初始化最大值纪录，O(1)
   for ( int i = 0; i < n; i++ ) //对全部共O(n)个元素，逐一
      m = max( m, A[i] ); //比较并更新，O(1)
   return m; //返回最大值，O(1)
} //O(1) + O(n) * O(1) + O(1) = O(n + 2) = O(n)
