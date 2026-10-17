#pragma once

template <typename T, typename V> void postorder( BNP<T> x, V& visit ) {
   if ( !x ) return;
   postorder( x->lc, visit );
   postorder( x->rc, visit );
   visit( x->data );
} //postorder
