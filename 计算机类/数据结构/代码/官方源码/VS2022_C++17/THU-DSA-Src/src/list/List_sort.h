#pragma once

template <typename T> void List<T>::sort( LNP<T> h, LNP<T> t ) {
   /*DSA*///switch( 3 ) {
   switch( rand() % 4 ) { //随机选取排序算法。可根据具体问题的特点灵活选取或扩充
      case 1  : insertionSort( h, t ); break; //插入排序
      case 2  : selectionSort( h, t ); break; //选择排序
      case 3  :     mergeSort( h, t ); break; //归并排序
      default :     radixSort( h, t ); break; //基数排序（第09章）
   } //switch
} //sort
