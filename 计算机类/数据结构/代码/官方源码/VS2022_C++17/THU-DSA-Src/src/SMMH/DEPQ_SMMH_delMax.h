#pragma once

template <typename T> T SMMH<T>::delMax() { //delMax from a non-empty SMMH
   if ( _size < 4 ) return _elem[--_size]; //trivial cases
   T maxElem = _elem[2]; Rank k = 2; _elem[k] = _elem[--_size]; //initialization
   while (1) { //percolate down
      Rank x = k;
      Rank i = rc(k); if ( (i < _size) && (_elem[i] > _elem[x]) ) x = i;
      Rank j = rn(k); if ( (j < _size) && (_elem[j] > _elem[x]) ) x = j;
      if ( x == k ) break;
      swap(_elem[k], _elem[x]); k = x; //Property #2
      if ( _elem[k-1] > _elem[k] ) swap( _elem[k-1], _elem[k]); //Property #0
   }
   return maxElem;
} //delMax
