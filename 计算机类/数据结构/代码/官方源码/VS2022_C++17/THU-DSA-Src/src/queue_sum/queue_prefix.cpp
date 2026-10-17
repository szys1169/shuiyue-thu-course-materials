/*DSA*/#include "queue_sum.h"

void qPreSum( Queue<int>& A, Rank n ) {
   int sum = 0; //前缀和
   while ( n-- ) //逐项累加
      A.enqueue( sum += A.dequeue() );
} //qPreSum, O(n)
