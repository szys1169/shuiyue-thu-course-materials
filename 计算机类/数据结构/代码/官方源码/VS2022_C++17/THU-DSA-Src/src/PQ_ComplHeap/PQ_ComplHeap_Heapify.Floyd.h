#pragma once

template <typename T> void heapify( T* A, const Rank n ) { //Floyd建堆算法，O(n)时间
   for ( Rank i = n / 2 - 1; - 1 != i; i-- ) //按照层次遍历的逆序，逐个地
      percolateDown( A, n, i ); //对每个内部节点做下滤，合并子堆
} //heapify
