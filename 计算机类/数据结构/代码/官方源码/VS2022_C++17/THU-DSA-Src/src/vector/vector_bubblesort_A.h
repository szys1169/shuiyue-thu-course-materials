#pragma once

template <typename T> void Vector<T>::bubbleSort( Rank lo, Rank hi ) {
   while ( lo < --hi ) //反复起泡扫描：最大元逐个就位，前缀[lo,hi)逐渐缩短
      for ( Rank i = lo; i < hi; i++ ) //逐对检查相邻元素
         if ( _elem[i] > _elem[i + 1] ) //若逆序
            swap( _elem[i], _elem[i + 1] ); //随即交换
} //bubbleSort，基本版
