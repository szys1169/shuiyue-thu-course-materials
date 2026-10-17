#pragma once

template <typename T> void List<T>::insertionSort( LNP<T> h, LNP<T> t ) {
   /*DSA*///printf( "InsertionSort ...\n" );
   for ( LNP<T> r = h->succ, s = r->succ; r != t; r = s, s = r->succ )
      r->moveSucc( search( h, r->data, r ) ); //在(h,r)内为[r]找到适当的位置，并插入
} //insertionSort
