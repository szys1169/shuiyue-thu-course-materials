#pragma once

/*DSA*/#include "queue/queue.h" //引入队列
template <typename T, typename V> void levelorder( BNP<T> x, V& visit ) {
   Queue<BNP<T>> Q; Q.enqueue( x ); //引入辅助队列，根节点入队
   while ( !Q.empty() ) { //在队列再次变空之前，反复迭代
      x = Q.dequeue(); visit( x->data ); //取出队首节点并访问之
      if ( x->lc ) Q.enqueue( x->lc ); //左孩子入队
      if ( x->rc ) Q.enqueue( x->rc ); //右孩子入队
   }
} //levelorder
