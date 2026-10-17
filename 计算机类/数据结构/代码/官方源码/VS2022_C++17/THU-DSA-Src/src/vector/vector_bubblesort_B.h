#pragma once

template <typename T> void Vector<T>::bubbleSort( Rank lo, Rank hi ) {
   for ( bool sorted = false; sorted = !sorted; hi-- ) //反复起泡扫描：前缀[lo,hi)逐渐缩短
      for ( Rank i = lo+1; i < hi; i++ ) //逐对检视相邻元素
         if ( _elem[i - 1] > _elem[i] ) //若逆序（前缀尚未有序）
            swap( _elem[i - 1], _elem[i] ), sorted = false; //随即交换
} //bubbleSort，提前终止版
