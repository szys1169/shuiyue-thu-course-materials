#pragma once

template <typename T> void Vector<T>::shellSort( Rank lo, Rank hi ) {
   /*DSA*/ //printf( "Shellsort [%3d, %3d)\n", lo, hi );
   for ( Rank d = 0x7FFFFFFF; 0 < d; d >>= 1 ) //PS Sequence: { 1, 3, 7, 15, 31, ... }
      for ( Rank j = lo + d; j < hi; j++ ) { //for each j in [lo+d, hi)
         T x = _elem[j]; Rank i = j; //within the prefix of the subsequence of [j]
         while ( ( lo + d <= i ) && ( x < _elem[i - d] ) ) //find the appropriate
            _elem[i] = _elem[i - d], i -= d; //predecessor [i]
         _elem[i] = x; //where to insert [j]
      }
} //shellSort
