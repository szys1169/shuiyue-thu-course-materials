#pragma once

template <typename T, typename V> void inorder( BNP<T> x, V& visit ) {
   if ( !x ) return;
   inorder( x->lc, visit );
   visit( x->data );
   inorder( x->rc, visit );
} //inorder
