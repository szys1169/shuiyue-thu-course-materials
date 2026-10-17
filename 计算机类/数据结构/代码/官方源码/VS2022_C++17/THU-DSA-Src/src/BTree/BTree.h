#pragma once

#include "BTNode.h"

template <typename T> struct BTree {
   Rank _size, _m; BTNP<T> _root; //关键码总数、阶次、根节点
   void solveOverflow( BTNP<T> ); //上溢修复
   void solveUnderflow( BTNP<T> ); //下溢修复
   BTree( Rank m = 3 ) : _m( m ), _size( 0 ), _root( new BTNode<T>() ) {}
   ~BTree() { clean( _root ); } //释放所有节点
   BTNP<T> search( const T& ); //查找
   bool insert( const T& ); //插入
   bool remove( const T& ); //删除
}; //BTree
/*DSA*/
/*DSA*/#include "BTree_search.h" //查找
/*DSA*/#include "BTree_insert.h" //插入
/*DSA*/#include "BTree_remove.h" //删除
/*DSA*/#include "BTree_clean.h" //清空
/*DSA*/#include "BTree_solveOverflow.h" //节点上溢处理
/*DSA*/#include "BTree_solveUnderflow.h" //节点下溢处理
