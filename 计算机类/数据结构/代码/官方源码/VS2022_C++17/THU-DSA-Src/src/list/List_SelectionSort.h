#pragma once

template <typename T> void List<T>::selectionSort( LNP<T> h, LNP<T> t ) {
   /*DSA*///printf( "SelectionSort ...\n" );
   for ( ; h->succ != t; t = t->pred ) //反复从无序前缀(h,t)中
      getMax(h, t)->movePred(t); //找出最大者，并将其转至有序后缀[t,...)的前端
      /*DSA*///swap(t->pred->data, selectMax( h->succ, n )->data );
} //selectionSort
