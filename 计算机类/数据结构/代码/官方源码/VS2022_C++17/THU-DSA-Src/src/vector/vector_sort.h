#pragma once

template <typename T> void Vector<T>::sort( Rank lo, Rank hi ) {
   if ( lo + 2 > hi ) return; //退化情况，统一处理
   //*DSA*/switch( 5 ) {
   switch ( rand() % 6 ) { //随机选择算法以充分测试；实际中可视具体环境灵活取舍或扩充
      case 1 :    bubbleSort( lo, hi ); break; //起泡排序
      case 2 : selectionSort( lo, hi ); break; //选择排序（习题）
      case 3 :     mergeSort( lo, hi ); break; //归并排序
      case 4 :      heapSort( lo, hi ); break; //堆排序（第12章）
      case 5 :     quickSort( lo, hi ); break; //快速排序（第14章）
      default :    shellSort( lo, hi ); break; //希尔排序（第14章）
   } //switch
} //sort
