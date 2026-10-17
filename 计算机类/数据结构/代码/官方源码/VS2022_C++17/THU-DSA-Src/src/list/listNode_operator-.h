#pragma once

template <typename T> //重载减号操作符，统计列表区间[h,this)的宽度
Rank ListNode<T>::operator-( LNP<T> h ) { //h <= this
   for ( Rank n = 0; ; h = h->succ, n++ )
      if ( h == this ) return n; //区间内的节点，挨个报数
} //O(n)
