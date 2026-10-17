#pragma once

template <typename T> T List<T>::remove( LNP<T> p ) { //O(1)
   T e = p->data; //备份数据项（T类型可直接赋值）
   p->pred->succ = p->succ; p->succ->pred = p->pred; //短路联接（pred|succ或为head|tail）
   delete p; _size--; return e; //释放节点，更新规模，返回数据项
} //remove
