#pragma once

template <typename T> void Vector<T>::mergeSort( Rank lo, Rank hi ) {
   /*DSA*/ //printf( "\tMERGEsort [%3d, %3d)\n", lo , hi );
   if ( hi - lo < 2 ) return; //单元素自然有序，否则
   Rank mi = ( lo + hi ) / 2; //均分为前缀、后缀
   mergeSort( lo, mi ); mergeSort( mi, hi ); //各自排序
   merge( lo, mi, hi ); //归并（实质的计算），O(n)
} //mergeSort, O(nlogn)
