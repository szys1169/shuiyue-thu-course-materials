#pragma once

template <typename T> void Vector<T>::quickSort( Rank lo, Rank hi ) {
   /*DSA*/ //printf( "\tQUICKsort [%3d, %3d)\n", lo, hi );
   if ( hi - lo < 2 ) return; //单元素区间自然有序，否则...
   Rank mi = partition( lo, hi ); //在[lo, hi)内构造轴点
   quickSort( lo, mi ); quickSort( mi + 1, hi ); //前缀、后缀各自递归排序
} //quickSort
