#pragma once

template <typename T> BNP<T> clone( BNP<T> t ) { //深复制
   if ( !t ) return nullptr;
   return new BinNode<T>( t->data, nullptr, clone(t->lc), clone(t->rc), t->height, t->color );
} //clone: p ~ Parent; t ~ source Tree
template <typename T> BinTree<T>::BinTree( BNP<T> t ) //复制子树
   { _root = clone( t ); _size = t->size(); }
template <typename T> BinTree<T>::BinTree( const BinTree<T>& t ) //复制全树
   { _root = clone( t._root ); _size = t.size(); }
template <typename T> BinTree<T>& BinTree<T>::operator=( const BinTree<T>& t ) { //赋值
   if ( _root != t._root )
      { remove( _root ); _root = clone( t._root ); _size = t.size(); }
   return *this;
} //operator=
