#pragma once

template <typename T> void UniPrint::p( PQ_List<T>& pq ) { //打印输出PQ_List
   printf( "%s*%d:\n", typeid( pq ).name(), pq.size() ); //基本信息
   p( ( List<T>& ) pq ); printf( "\n" );
}
