#pragma once

/*DSA*/#include "BST/BST.h"
/*DSA*/
template <typename T> class AVL : public BST<T,false> {
public: //基于BST实现AVL树
   BNP<T> insert( const T& ); //插入（重写）
   bool remove( const T& ); //删除（重写）
   //BST::search()等其余接口可直接沿用
}; //AVL
/*DSA*/
/*DSA*/#include "AVL_insert.h" //插入
/*DSA*/#include "AVL_remove.h" //删除
