#pragma once

template <typename T> BNP<T> clone( BNP<T> p, BNP<T> t ) { //深复制
   if ( !t ) return nullptr;
   BNP<T> x = new BinNode<T>( t->data, p, nullptr, nullptr, t->height, t->color ); //先序
   x->lc = clone( x, t->lc ); x->rc = clone( x, t->rc );
   return x; //由t复制出x
} //clone: p ~ Parent; t ~ source Tree
/*DSA*/template <typename T> BinTree<T>::BinTree( BNP<T> t ) //复制子树
/*DSA*/   { _root = clone( nullptr, t ); _size = t->size(); }
/*DSA*/
/*DSA*/template <typename T> BinTree<T>::BinTree( const BinTree<T>& t ) //复制全树
/*DSA*/   { _root = clone<T>( nullptr, t._root ); _size = t.size(); }
/*DSA*/
template <typename T> BinTree<T>& BinTree<T>::operator=( const BinTree<T>& t ) { //赋值
   if ( _root != t._root )
      { remove( _root ); _root = clone<T>( nullptr, t._root ); _size = t.size(); }
   return *this;
} //operator=
