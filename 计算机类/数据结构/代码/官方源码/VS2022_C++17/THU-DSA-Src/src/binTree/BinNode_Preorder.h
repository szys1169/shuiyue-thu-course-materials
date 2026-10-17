#pragma once

template <typename T, typename V> void preorder( BNP<T> x, V& visit ) {
   if ( !x ) return;
   visit( x->data );
   preorder( x->lc, visit );
   preorder( x->rc, visit );
} //preorder
