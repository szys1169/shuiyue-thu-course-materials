#pragma once

template <typename T> void ListNode<T>::movePred( LNP<T> s ) { //O(1)
   pred->succ = succ; succ->pred = pred; //取出当前节点
   pred = s->pred; pred->succ = this; succ = s; s->pred = this; //转移到紧靠于s之前
} //this == s时相当于原地不动，故通常不需作此判断

template <typename T> void ListNode<T>::moveSucc( LNP<T> p ) { //O(1)
   succ->pred = pred; pred->succ = succ; //取出当前节点
   succ = p->succ; succ->pred = this; pred = p; p->succ = this; //转移到紧接于p之后
}  //p == this时相当于原地不动，故通常不需作此判断
