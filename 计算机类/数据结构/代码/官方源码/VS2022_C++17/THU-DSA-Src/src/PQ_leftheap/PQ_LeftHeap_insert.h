#pragma once

template <typename T> void PQ_LeftHeap<T>::insert( T e ) {
   _root = merge( _root, new BinNode<T>( e, nullptr, nullptr, nullptr, 1 ) );
   _size++; //将e封装为左式堆（初始NPL为1），与当前左式堆合并后，更新规模
} //insert
