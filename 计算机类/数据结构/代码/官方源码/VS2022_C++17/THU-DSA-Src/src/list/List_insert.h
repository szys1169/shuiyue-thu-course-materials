#pragma once

template <typename T> LNP<T> List<T>::insertFirst( const T& e )
   { _size++; return head->insertSucc( e ); } //e当作首节点插入
template <typename T> LNP<T> List<T>::insertLast( const T& e )
   { _size++; return tail->insertPred( e ); } //e当作末节点插入
template <typename T> LNP<T> List<T>::insert( LNP<T> p, const T& e )
   { _size++; return p->insertSucc( e ); } //e当作p的后继插入
template <typename T> LNP<T> List<T>::insert( const T& e, LNP<T> p )
   { _size++; return p->insertPred( e ); } //e当作p的前驱插入
