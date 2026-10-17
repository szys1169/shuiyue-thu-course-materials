#pragma once

template <typename T> LNP<T> List<T>::join( List<T>& L ) { //L作为后缀接入当前列表
   if ( L._size < 1 ) return nullptr;
   LNP<T> first = L.head->succ;
   tail->pred->succ = L.head->succ;
   L.head->succ->pred = tail->pred;
   L.tail->pred->succ = tail;
   tail->pred = L.tail->pred;
   _size += L._size;
   L.head->succ = L.tail;
   L.tail->pred = L.head;
   L._size = 0;
   return first;
} //O(1)
