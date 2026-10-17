#pragma once

template <typename T> void Vector<T>::uniquify() { //有序向量去重算法（低效版）
   for ( Rank i = 1; i < _size; ) //从前向后，逐一比对相邻的[i-1]和[i]
      if ( _elem[i-1] != _elem[i] ) i++; //若不等，则转至下一对元素
      else remove (i); //否则，删除靠后者
} //uniquify, O(n^2)
