#pragma once

template <typename T> void List<T>::init() { //列表初始化，在创建列表对象时统一调用
   head = new ListNode<T>; tail = new ListNode<T>; //创建头、尾哨兵节点
   head->succ = tail; head->pred = nullptr; //向前链接
   tail->pred = head; tail->succ = nullptr; //向后链接
   _size = 0; //记录规模
} //init
