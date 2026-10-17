#pragma once

template <typename T> //在有序向量的区间[lo,hi)内，找出不大于e的最后一个节点
Rank Vector<T>::search( const T& e, Rank lo, Rank hi ) const { //0 <= lo < hi <= _size
   return( rand() % 2 ) ? binSearch( _elem, e, lo, hi ) : fibSearch( _elem, e, lo, hi );
} //为便于测试，暂且随机地调用两类算法；在实际应用中，你可针对具体问题选用最适宜的一种
