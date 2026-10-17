#pragma once

template <typename T> //在无序列表区间(h,t)内，找到等于e的最靠后者：h < t
LNP<T> List<T>::find( LNP<T> h, const T& e, LNP<T> t ) const {
   while ( h != (t = t->pred ) ) //自后向前
      if ( e == t->data ) return t; //逐个比对，直至命中（假定类型T已重载“==”）
   return nullptr; //或失败
} //find：O(n)
