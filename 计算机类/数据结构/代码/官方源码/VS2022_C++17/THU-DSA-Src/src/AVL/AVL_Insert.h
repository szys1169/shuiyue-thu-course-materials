#pragma once

template <typename T> BNP<T> AVL<T>::insert( const T& e ) {
   BST::insert( e ); if ( _p == _x ) return _x; //先按BST规则插入
   for ( BNP<T> g = _p; g; g = g->parent ) { //逐层上溯历代祖先g
      if ( !AvlBalanced( g ) ) g = rotate( g ); //一旦g失衡，则经旋转使之复衡
      g->updateHeight(); if ( 0 == BalFac( g ) ) break; //可能提前终止上溯
   } //局部子树复衡后，高度必然复原；所有祖先亦必复衡：累计至多O(1)次旋转
   return _x; //插入成功
} //insert
