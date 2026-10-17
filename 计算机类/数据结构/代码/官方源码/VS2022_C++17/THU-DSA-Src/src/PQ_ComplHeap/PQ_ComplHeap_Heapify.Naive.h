#pragma once

template <typename T> void heapify( T* A, const Rank n ) { //蛮力建堆算法，O(nlogn)时间
   for ( Rank i = 1; i < n; i++ ) //按照层次遍历次序，逐个对节点做上滤
      percolateUp( A, i ); //等效于省略Vector::insert(A[i]，直接插入
} //heapify
