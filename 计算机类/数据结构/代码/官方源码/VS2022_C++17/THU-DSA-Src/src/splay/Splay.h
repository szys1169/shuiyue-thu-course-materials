#pragma once

#include "BST/BST.h" //基于BST实现Splay
template <typename T> class Splay : public BST<T> { //由BST派生的Splay树模板类
protected:
   BNP<T> splay( BNP<T> ); //将节点伸展至根
public:
   BNP<T> search( const T&  ); //查找（重写）
   BNP<T> insert( const T& ); //插入（重写）
   bool remove( const T& ); //删除（重写）
}; //Splay
/*DSA*/
/*DSA*/#include "Splay_search.h" //查找
/*DSA*/#include "Splay_insert.h" //插入
/*DSA*/#include "Splay_remove.h" //删除
/*DSA*/#include "Splay_splay.h" //伸展调整
