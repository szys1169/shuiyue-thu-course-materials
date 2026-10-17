#pragma once

template <typename T> //归并：(h,y) + [y,t)
void List<T>::merge( LNP<T> h, LNP<T> y, LNP<T> t ) {
   for ( LNP<T> x = h->succ; (x != y) && (y != t); )
      if ( x->data > y->data ) //小者优先；相等时x优先，以保证稳定性
         (y = y->succ)->pred->movePred(x);
      else
         x = x->succ;
} //O(n+m)
