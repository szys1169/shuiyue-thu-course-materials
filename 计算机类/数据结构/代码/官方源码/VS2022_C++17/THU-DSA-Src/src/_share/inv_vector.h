#pragma once

/*DSA*/#include "vector/vector.h"
/*DSA*/
template <typename T> int inv( Vector<T>& V ) //统计向量中相邻逆序对的总数
   { int invs = 0;  V.traverse( Compare<T>( invs, V[0] ) );  return invs; }
