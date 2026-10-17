#pragma once

template <typename T> Rank percolateUp( T* A, Rank i ) { //0 <= i < _size
   for ( Rank j; (0 < i) && (A[j = Parent(i)] < A[i]); i = j ) //自下而上，逐层检视
      swap( A[i], A[j] ); //只要父不如子，随即易位
   return i; //返回最终抵达的位置
} //percolateUp
