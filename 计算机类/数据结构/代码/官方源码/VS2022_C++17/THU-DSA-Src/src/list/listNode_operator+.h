#pragma once

template <typename T> //重载加号操作符，以通过秩直接访问列表节点
LNP<T> ListNode<T>::operator+( Rank r ) { // 0 <= r < size - this
   for ( LNP<T> p = this; ; p = p->succ, r-- ) //从当前节点出发
      if ( 0 == r ) return p; //顺数第r个节点即是目标节点
} //O(r)：虽方便，勿多用
