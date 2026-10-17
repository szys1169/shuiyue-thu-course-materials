#pragma once

template <typename T> void List<T>::reverse() { //前后倒置
   if ( _size < 2 ) return; //平凡情况
   for ( LNP<T> p = head; p; p = p->pred ) //自前向后，依次
      swap( p->pred, p->succ ); //交换各节点的前驱、后继指针
   swap( head, tail ); //头、尾节点互换
} //reverse()
