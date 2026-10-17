#pragma once

template <typename T> bool AVL<T>::remove( const T& e ) {
   if ( !BST::remove( e ) ) return false; //先按BST规则删除
   for ( BNP<T> g = _p; g; g = g->parent ) { //逐层上溯历代祖先g
      if ( !AvlBalanced( g ) ) g = rotate( g ); //每当g失衡，都经旋转使之复衡
      g->updateHeight(); if ( 0 != BalFac( g ) ) break; //可能提前终止上溯
   } //局部子树复衡后，高度未必复原；更高祖先仍或失衡：累计可能Omega(logn)次旋转
   return true; //删除成功
} //remove
