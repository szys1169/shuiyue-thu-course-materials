#pragma once

template <typename T> BNP<T> BinTree<T>::insert( const T& e )
   { _size = 1; return _root = new BinNode<T>( e ); } //e作为根节点插入（空）二叉树
template <typename T> BNP<T> BinTree<T>::insert( const T& e, BNP<T> x )
   { _size++; x->insertLc( e ); x->updateHeightAbove(); return x->lc; } //e插入为x的左孩子
template <typename T> BNP<T> BinTree<T>::insert( BNP<T> x, const T& e )
   { _size++; x->insertRc( e ); x->updateHeightAbove(); return x->rc; } //e插入为x的右孩子
