#pragma once

#include "BST/BST.h"
template <typename T> class RedBlack : public BST<T,false> { //基于BST派生出RedBlack
protected:
   void solveDoubleRed(); //双红修正
   void solveDoubleBlack(); //双黑修正
public:
   BNP<T> insert( const T& ); //插入（重写）
   bool remove( const T& ); //删除（重写）
//BST::search()等其余接口可直接沿用
}; //RedBlack
/*DSA*/
/*DSA*/#include "RedBlack_insert.h" //插入
/*DSA*/#include "RedBlack_remove.h" //删除
/*DSA*/#include "RedBlack_solveDoubleRed.h" //双红修正
/*DSA*/#include "RedBlack_solveDoubleBlack.h" //双黑修正
