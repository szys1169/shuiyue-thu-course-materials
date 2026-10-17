#pragma once

#include "List/List.h" //基于列表实现
#include "PQ/PQ.h" //优先级队列A
template <typename T> class PQ_List : public PQ<T>, public List<T> {
   /*DSA*/friend class UniPrint; //演示输出使用，否则不必设置友类
public:
   PQ_List( T* E = nullptr, int n = 0 ) { while ( 0 < n-- ) insertFirst( E[n] ); } //构造
   void insert( T e ) { insertLast( e ); } //新元素直接插至队尾
   T delMax() { return remove( List::getMax() ); } //删除最优先的元素
   T& getMax() { return List::getMax()->data; } //取出最优先的元素
}; //PQ_List
