#pragma once

template <typename T> Rank percolateDown( T* A, Rank n, Rank i ) { //0 <= i < _size
   for ( Rank j; i != ( j = ProperParent( A, n, i ) ); i = j ) //自上而下，逐层检视
      swap( A[i], A[j] ); //只要i不堪为父，随即与更强的孩子j易位
   return i; //返回最终抵达的位置（亦i亦j）
} //percolateDown
