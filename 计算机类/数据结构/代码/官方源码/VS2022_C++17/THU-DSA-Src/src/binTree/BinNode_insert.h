#pragma once

template <typename T> BNP<T> BinNode<T>::insertLc( const T& e ) //将e作为左孩子插入
   { return lc = new BinNode<T>( e, this ); } //右孩子的插入完全对称，请自行补充
/*DSA*/
/*DSA*/template <typename T> BNP<T> BinNode<T>::insertRc( const T& e ) //将e作为右孩子插入
/*DSA*/   { return rc = new BinNode<T>( e, this ); } //左孩子的插入完全对称，请自行补充
