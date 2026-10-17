#pragma once

template <typename T> void List<T>::mergeSort( LNP<T> h, LNP<T> t ) {
   /*DSA*///printf( "\tMERGEsort...\n" );
   Rank n = *t - h - 1; //区间长度
   if ( n < 2 ) return; //不足2时，直接返回；否则...
   LNP<T> x = *h + n/2; //切分：(h,t) = (h,x] + (x,t)
   mergeSort( x, t ); //后缀与
   mergeSort( h, x = x->succ ); //前缀各自排序
   merge( h, x, t ); //归并：(h,x) + [x,t)
} //mergeSort
