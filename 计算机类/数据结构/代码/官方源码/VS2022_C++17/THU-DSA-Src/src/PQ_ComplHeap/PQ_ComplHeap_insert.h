#pragma once

template <typename T> void PQ_ComplHeap<T>::insert( T e ) {
   Vector<T>::insert( e ); //将新词条接至向量末尾
   percolateUp( _elem, _size - 1 ); //再对该词条上滤调整
} //insert
