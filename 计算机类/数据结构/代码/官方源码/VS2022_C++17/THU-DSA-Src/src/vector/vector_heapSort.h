#pragma once

template <typename T> void Vector<T>::heapSort( Rank lo, Rank hi ) { //0 <= lo < hi <= size
   /*DSA*/ //printf( "\tHEAPsort [%3d, %3d)\n", lo, hi );
   T* A = _elem + lo; Rank n = hi - lo; heapify( A, n ); //将待排序区间建成一个完全二叉堆，O(n)
   while ( 0 < --n ) //反复地摘除最大元并归入已排序的后缀，直至堆空
      { swap( A[0], A[n] ); percolateDown( A, n, 0 ); } //堆顶与末元素对换，再下滤
} //heapSort
