#pragma once

template <typename T> BTNP<T> BTree<T>::search( const T& e ) {
   BTNP<T> x = _root; //自根而下
   for ( Rank k = -1; x->child[0]; x = x->child[k+1] ) { //逐层深入（I/O）
      k = x->key.search( e ); //简便起见用了二分查找，但此时改用顺序查找效率反而更高
      if ( -1 != k  &&  e == x->key[k] ) break; //一旦发现e，随即返回
   }
   return x; //成功时，x为e所属节点；失败时，x为可插入e的叶节点
} //search
