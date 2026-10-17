#pragma once

/*DSA*/template <typename T>
/*DSA*/void Vector<T>::traverse( void ( *visit )( T& ) ) // 借助函数指针机制
/*DSA*/   { for ( Rank i = 0; i < _size; i++ ) visit( _elem[i] ); } //遍历向量
/*DSA*/
template <typename T> template <typename VST>
void Vector<T>::traverse( VST& visit ) //借助函数对象机制
   { for ( Rank i = 0; i < _size; i++ ) visit( _elem[i] ); } //遍历向量
