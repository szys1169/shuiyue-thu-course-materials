#pragma once

template <typename T> void List<T>::dedup() { //O(n^2)
   for ( LNP<T> p = first(); p != tail; p = p->succ ) //在无重的前缀(head,p)中
      if ( LNP<T> q = find( head, p->data, p ) ) //一旦发现有q与p相等
         remove(q); //便删除前者（如此更简明，而Vector::dedup()删除后者效率更高）
} //dedup
