#pragma once

template <typename T> void clean( BTNP<T> x ) {
   if ( !x ) return;
   for ( Rank k = 0; k < x->child.size(); k++ )
      clean( x->child[k] );
   delete x;
} //clean
