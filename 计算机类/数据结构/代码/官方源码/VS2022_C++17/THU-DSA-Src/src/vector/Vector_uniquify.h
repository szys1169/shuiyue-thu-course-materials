#pragma once

template <typename T> void Vector<T>::uniquify() { //有序向量去重算法（高效版）
   Rank i = 0; //前缀[0,i]包含目前已知的所有无重元素
   for ( Rank j = 1; j < _size; j++ ) //逐一考查[j]
      if ( _elem[i] != _elem[j] ) //不等，当且仅当[j]为一个区间的首元素
         _elem[++i] = _elem[j]; //故将[j]归入无重的前缀
   _size = ++i; shrink();
} //uniquify, O(n)
