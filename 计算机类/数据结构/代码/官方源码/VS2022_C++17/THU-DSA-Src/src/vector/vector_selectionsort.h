#pragma once

template <typename T> void Vector<T>::selectionSort( Rank lo, Rank hi ) {
   /*DSA*/ //printf( "Selectionsort [%3d, %3d)\n", lo, hi );
   while ( lo < --hi )
      swap( _elem[getMax( lo, hi )], _elem[hi] ); //将[hi]与[lo, hi]中的最大者交换
} //selectionSort

template <typename T> Rank Vector<T>::getMax( Rank lo, Rank hi ) {
   Rank mx = hi;
   while ( lo < hi-- ) //逆向扫描
      if ( _elem[hi] > _elem[mx] ) //且严格比较
         mx = hi; //故能在max有多个时保证后者优先，进而保证selectionSort稳定
   return mx;
} //getMax
