#pragma once

template <typename T> //从区间(h,t)中选出最大者（若有多个，取最靠后者）：h < t
LNP<T> List<T>::getMax( LNP<T> h, LNP<T> t ) {
   for ( LNP<T> x = t = t->pred; x != h; x = x->pred ) //从后向前，逐个比较
      if ( t->data < x->data ) //见贤：优先级高低，取决于比较器
         t = x; //思齐
   return t; //最大者
} //getMax：O(n)
