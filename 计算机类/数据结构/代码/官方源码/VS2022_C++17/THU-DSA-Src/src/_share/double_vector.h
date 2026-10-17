#pragma once

template <typename T> void double( Vector<T> & V ) //统一加倍向量中的各元素
   { V.traverse( Double<T>() ); } //以Double<T>()为基本操作进行遍历
