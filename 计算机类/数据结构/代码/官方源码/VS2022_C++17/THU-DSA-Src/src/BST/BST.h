#pragma once

/*DSA*/#include "BinTree/BinTree.h" //引入BinTree
/*DSA*/
template <typename T, bool H = true> //H：是否按BST规则更新高度
class BST : public BinTree<T> { //由BinTree派生BST模板类
protected:
   BNP<T> _x, _p, _r; //查找的终点、其父亲，以及删除之后的替代者
   BNP<T> connect342( BNP<T>, BNP<T>, BNP<T>, BNP<T>, BNP<T> ); //“3+4-2”重构
   BNP<T> rotate( BNP<T> ); //局部旋转调整
public: //基本接口：以virtual修饰，派生的BST变种可默认继承，也可根据各自的规则重写
   virtual BNP<T> search( const T& ); //查找
   virtual BNP<T> insert( const T&, int h = 0 ); //插入（新节点作为叶子，高度为0）
   virtual bool remove( const T& ); //删除
   /*DSA*/
   /*DSA*/void stretchToLPath() { stretchByZag( _root ); } //借助zag旋转，转化为左向单链
   /*DSA*/void stretchToRPath() { stretchByZig( _root ); } //借助zig旋转，转化为右向单链
   /*DSA*/void stretch();
   /*DSA*/void balance() { _root = _root->balance(); }
   /*DSA*/void imitate( BST<T> Y ) { _root = _root->imitate( Y._root ); }
}; //BST
/*DSA*/
/*DSA*/#include "BST_search.h" //查找
/*DSA*/#include "BST_insert.h" //插入
/*DSA*/#include "BST_remove.h" //删除
/*DSA*/#include "BST_connect342.h"
/*DSA*/#include "BST_rotate.h"
