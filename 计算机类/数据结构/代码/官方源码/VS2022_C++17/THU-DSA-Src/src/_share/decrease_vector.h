#pragma once

template <typename T> void decrease( Vector<T> & V ) //统一递减向量中的各元素
   { V.traverse( Decrease<T>() ); } //以Decrease<T>()为基本操作进行遍历
