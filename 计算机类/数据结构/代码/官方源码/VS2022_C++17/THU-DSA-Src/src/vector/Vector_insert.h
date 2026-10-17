#pragma once

template <typename T> void Vector<T>::insert( Rank r, const T& e ) //0 <= r <= _size
{ insert( r, &e, 0, 1 ); } //单元素插入

template <typename T> //T为基本类型，或已重载赋值操作符'='；S <> this
void Vector<T>::insert( Rank r, const T* A, Rank lo, Rank hi ) { //将A[lo,hi)插至[r]
   Rank d = hi - lo;  expand( d ); //若必要，先扩容：确保足以新增d个元素
   for ( Rank i = _size - 1; i != r - 1; i-- ) //长度为n-r的后缀：自后向前地后移
      _elem[i + d] = _elem[i]; //O(n-r)
   while ( lo < hi ) //插入d个元素
      _elem[r++] = A[lo++]; //O(d)
   _size += d;
} //insert, O(n + d - r)
