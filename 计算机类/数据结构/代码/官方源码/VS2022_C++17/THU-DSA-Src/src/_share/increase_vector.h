#pragma once

/*DSA*/#include "vector/vector.h"

template <typename T> void increase( Vector<T>& V ) //统一递增向量中的各元素
   { V.traverse( Increase<T>() ); } //以Increase<T>()为基本操作进行遍历
