#pragma once

template <typename T> T PQ_ComplHeap<T>::delMax() {
   swap( _elem[0], _elem[--_size] ); //堆顶、堆尾互换（不致引发shrink()）
   percolateDown( _elem, _size, 0 ); //新堆顶下滤
   return _elem[_size]; //返回原堆顶
} //delMax
