#pragma once

template <typename T> void half ( List<T> & L ) //统一减半列表中的各元素
{  L.traverse ( Half<T>() );  } //以Half<T>()为基本操作进行遍历
