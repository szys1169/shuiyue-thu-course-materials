#pragma once

template <typename T> void UniPrint::p( Skiplist<T>& s ) { //Skiplist
   printf( "%s*%d*%d:\n", typeid( s ).name(), tower(s.head).size(), s.size() ); //基本信息
   for ( Rank h = tower(s.head).size(); 0 < h; h-- ) {
      print("-INF");
      for ( ListNode<Tower<T>>* x = s.head->succ; x != s.tail; x = x->succ )
         if ( tower(x).size() < h )
            print("----");
         else
            print( key(x) );
      print("+INF\n");
   }
   printf( "\n" );
}
