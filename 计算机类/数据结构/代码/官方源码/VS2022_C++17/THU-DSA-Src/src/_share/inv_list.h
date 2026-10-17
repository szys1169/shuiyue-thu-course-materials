#pragma once

#include "list/list.h"

template <typename T> int inv( List<T>& L ) //统计列表中相邻逆序对的总数
   { int invs = 0;  L.traverse( Compare<T>( invs, L[0]->data ) );  return invs; }
