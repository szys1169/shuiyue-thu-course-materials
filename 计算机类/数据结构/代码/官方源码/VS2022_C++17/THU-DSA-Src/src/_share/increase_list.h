#pragma once

/*DSA*/#include "list/list.h"

template <typename T> void increase( List <T>& L ) //统一递增列表中的各元素
   { L.traverse( Increase<T>() ); } //以Increase<T>()为基本操作进行遍历
