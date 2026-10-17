#pragma once

template <typename T> BNP<T> Splay<T>::search( const T& e ) {
   BST::search( e ); //按BST标准算法查找：无论结果如何，最后抵达的节点
   return _x ? splay(_x) : _p ? splay(_p) : nullptr;  //都将随即伸展为_root
} //search
