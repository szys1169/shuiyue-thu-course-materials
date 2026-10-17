#pragma once

#include "list/list.h"

template <typename T> T sum( List<T>& L ) //累计列表中所有元素的总和
   { T sum = 0;  L.traverse( Cumulate<T>( sum ) );  return sum; }
