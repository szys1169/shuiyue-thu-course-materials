/*DSA*/#include "queue_sum.h"

void qWinSum( Queue<int>& A, Rank n, Rank w ) { //w<=n
   qPreSum( A, n ); //先求前缀和
   Queue<int> W; W.enqueue( 0 ); //建立窗口
   for ( Rank i = 1; i < w; i++ ) //充满窗口
      W.enqueue( A.dequeue() );
   /*DSA*/print( A ); print( W );
   for ( Rank i = w-1; i < n; i++ ) { //逐项
      A.enqueue( A.front() - W.dequeue() ); //求差
      W.enqueue( A.dequeue() ); //滑动窗口
   } //for
} //qWinSum, O(n)
