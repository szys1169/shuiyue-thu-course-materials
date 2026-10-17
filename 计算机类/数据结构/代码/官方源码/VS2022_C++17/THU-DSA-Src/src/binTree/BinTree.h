#pragma once

/*DSA*/#include "BinNode.h" //引入二叉树节点类
template <typename T> class BinTree { //二叉树模板类
protected:
   Rank _size; BNP<T> _root; //规模、根节点
public:
   BinTree() : _size( 0 ), _root( nullptr ) {} //构造
   ~BinTree() { remove( _root ); } //析构
   BinTree( const BinTree<T>& ); //复制
   BinTree( const BNP<T> ); //复制
   Rank size() const { return _size; } //规模
   bool empty() const { return !_root; } //判空
   BNP<T> root() const { return _root; } //树根
   BNP<T> insert( const T& ); //插入根节点
   BNP<T> insert( const T&, BNP<T> ); //插入左孩子
   BNP<T> insert( BNP<T>, const T& ); //插入右孩子
   BNP<T> attach( BinTree<T>, BNP<T> ); //接入左子树
   BNP<T> attach( BNP<T>, BinTree<T> ); //接入右子树
   BinTree<T> secede( BNP<T> ); //子树分离
   Rank remove( BNP<T> ); //子树删除
   template <typename V> void traverse(V& visit ) //遍历
      { if ( _root ) _root->traverse( visit ); }
   BinTree<T>& operator= ( const BinTree<T>& ); //赋值
   bool operator<( BinTree<T> const& t ) //比较器（示例一个，其余自行补充）
      { return _root && t._root && ( _root->data < t._root->data ); }
}; //BinTree
/*DSA*/
/*DSA*/#include "BinTree_attach.h"
/*DSA*/#include "BinTree_remove.h"
/*DSA*/#include "BinTree_secede.h"
/*DSA*/#include "BinTree_copy_pre.h"
/*DSA*/#include "BinTree_insert.h"
/*DSA*///#include "BinTree_copy_post.h"
