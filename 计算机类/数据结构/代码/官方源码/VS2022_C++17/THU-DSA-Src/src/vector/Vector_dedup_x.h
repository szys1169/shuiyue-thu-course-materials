#pragma once

template <typename T> void Vector<T>::dedup() { //O(n^2)
   for ( Rank i, j = 0; j < _size; j++ ) {
      for ( i = 0; _elem[i] != _elem[j]; i++ ); //在[0,j]中查找[j]：[j]相当于哨兵，故必终止
      if ( i != j ) //若发现重复
         for ( j--, _size--; i < _size; i++ ) //则令后缀前移（[i]被覆盖|删除）
            _elem[i] = _elem[i+1];
   } //for
} //dedup：优先删除靠前者，复杂度常系数略高
