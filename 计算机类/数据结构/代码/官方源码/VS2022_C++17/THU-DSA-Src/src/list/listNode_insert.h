#pragma once

template <typename T> //紧靠当前节点之前，将e插入列表：O(1)
LNP<T> ListNode<T>::insertPred( const T& e ) {
   LNP<T> x = new ListNode( e, pred, this ); //创建新节点（pred或为head）
   pred->succ = x; pred = x; return x; //列表接纳新节点（操作次序不可颠倒）
} //insertPred
template <typename T> //紧随当前节点之后，将e插入列表：O(1)
LNP<T> ListNode<T>::insertSucc( const T& e ) {
   LNP<T> x = new ListNode( e, this, succ ); //创建新节点（succ或为tail）
   succ->pred = x; succ = x; return x; //列表接纳新节点（操作次序不可颠倒）
} //insertSucc
