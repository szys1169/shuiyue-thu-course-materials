#pragma once

template <typename T> void Vector<T>::copy( const T* A, Rank lo, Rank hi ) {
   for ( _size = 0; lo < hi; _size++, lo++ ) //A[lo,hi)复制至_elem[0,hi-lo)
      _elem[ _size ] = A[ lo ]; //T若非基本类型，则需重载操作符'='以实现深复制
} //copy, O(hi-lo)
