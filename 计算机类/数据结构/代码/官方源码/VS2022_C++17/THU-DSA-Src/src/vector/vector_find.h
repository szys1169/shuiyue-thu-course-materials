#pragma once

template <typename T> //0 <= lo < hi <= _size
Rank Vector<T>::find( const T& e, Rank lo, Rank hi ) const { //O(hi-lo)
   while ( ( lo < hi-- ) && ( e != _elem[hi] ) ); //从后向前，逐个比对
   return hi; //最靠后的命中者，或lo-1示意失败（lo==0时为-1 == UINT_MAX）
} //find
