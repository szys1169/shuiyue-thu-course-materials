#pragma once

template <typename T> void List<T>::reverse() { //前后倒置
   if ( _size < 2 ) return; //平凡情况
   LNP<T> p, q;
   for ( p = head, q = p->succ; p != tail; p = q, q = p->succ )
      p->pred = q; //自前向后，依次颠倒各节点的前驱指针
   tail->pred = nullptr; //单独设置尾节点的前驱指针
   for ( p = head, q = p->pred; p != tail; p = q, q = p->pred )
      q->succ = p; //自前向后，依次颠倒各节点的后继指针
   head->succ = nullptr; //单独设置头节点的后继指针
   swap( head, tail ); //头、尾节点互换
} //reverse()
