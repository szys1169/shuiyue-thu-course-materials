#pragma once

template <typename T> Vector<T>& Vector<T>::operator= ( Vector<T> const& V ) { //深复制
   _size = 0; //删除原有内容
   expand( V._size ); copy( V._elem, 0, V._size ); //整体复制
   return *this; //返回当前向量的引用，以便链式赋值
} //operator=
