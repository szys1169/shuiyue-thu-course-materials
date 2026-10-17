#pragma once

#include "PQ/PQ.h" //按照优先级队列ADT实现的
#include "Vector/Vector.h" //借助多重继承机制，基于向量
template <typename T> struct PQ_ComplHeap : public PQ<T>, public Vector<T> { //完全二叉堆
   //*DSA*/ friend class UniPrint; //演示输出使用，否则不必设置友类
   PQ_ComplHeap() {} //默认构造
   PQ_ComplHeap( T* A, Rank n ) { expand(n); copy(A, 0, n); heapify(_elem, n); } //批量构造
   void insert( T ); //按照比较器确定的优先级次序，插入词条
   T delMax(); //删除优先级最高的词条
   T& getMax(); //读取优先级最高的词条
}; //PQ_ComplHeap
template <typename T> void heapify( T* A, Rank n ); //Floyd建堆算法
template <typename T> Rank percolateDown( T* A, Rank n, Rank i ); //下滤
template <typename T> Rank percolateUp( T* A, Rank i ); //上滤
/*DSA*/
/*DSA*/#include "PQ_ComplHeap_macro.h"
/*DSA*/#include "PQ_ComplHeap_Insert.h"
/*DSA*/#include "PQ_ComplHeap_getMax.h"
/*DSA*/#include "PQ_ComplHeap_delMax.h"
/*DSA*/#include "PQ_ComplHeap_percolateUp.h"
/*DSA*/#include "PQ_ComplHeap_percolateDown.h"
/*DSA*///#include "PQ_ComplHeap_heapify.Naive.h"
/*DSA*/#include "PQ_ComplHeap_heapify.Floyd.h"
