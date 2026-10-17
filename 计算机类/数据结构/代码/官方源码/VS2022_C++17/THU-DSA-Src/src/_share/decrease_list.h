#pragma once

template <typename T> void decrease( List<T> & L ) //统一递减列表中的各元素
   { L.traverse( Decrease<T>() ); } //以Decrease<T>()为基本操作进行遍历
