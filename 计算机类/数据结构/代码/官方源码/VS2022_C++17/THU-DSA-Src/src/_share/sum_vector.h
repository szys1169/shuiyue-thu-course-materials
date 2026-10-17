#pragma once

/*DSA*/#include "vector/vector.h"
/*DSA*/
template <typename T> T sum( Vector<T>& V ) //累计向量中所有元素的总和
   { T sum = 0;  V.traverse( Cumulate<T>( sum ) );  return sum; }
