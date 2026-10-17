#pragma once

template <typename T> //在有序列表区间(h,t)内，找到不大于e的最靠后者：h < t
LNP<T> List<T>::search( LNP<T> h, const T& e, LNP<T> t ) const {
   if ( (h->succ == t) || (e < h->succ->data) ) return h; //越界情况，先做特判
   do  { t = t->pred; }  while ( e < t->data ); //自后向前，逐个比较
   return t; //直至不大于e的最靠后者
} //search：O(n)
