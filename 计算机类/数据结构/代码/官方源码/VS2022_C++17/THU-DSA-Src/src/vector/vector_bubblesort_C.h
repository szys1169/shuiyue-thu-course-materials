#pragma once

template <typename T> void Vector<T>::bubbleSort( Rank lo, Rank hi ) {
   for ( Rank last; lo < hi; hi = last ) //反复起泡扫描：最大元逐个就位，前缀[lo,hi)逐渐缩短
      for ( Rank i = ( last = lo ) + 1; i < hi; i++ ) //逐对检视相邻元素
         if ( _elem[i - 1] > _elem[i] ) //若逆序
            swap( _elem[i - 1], _elem[i] ), last = i; //随即交换，并记住交换位置
} //bubbleSort，跳跃版
