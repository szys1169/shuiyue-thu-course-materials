#pragma once

template <typename T> void Vector<T>::dedup() { //O(n^2)
   for ( Rank i = 1; i < _size; ) //自前向后逐个考查
      if ( -1 == find(_elem[i], 0, i) ) //在无重的前缀[0,i)中查找[i]，O(i)
         i++; //若无，则继续考查其后继
      else
         remove(i); //否则（至多一个）删除[i]，O(_size-i)
} //dedup
