/******************************************************************************************
* Test of PQ_ComplHeap& PQ_LeftHeap
 ******************************************************************************************/
#include "PQ_test.h"
//#include <windows.h>

template <typename PQ> void testPq( Rank n ) { //统一测试基于列表、向量以及左式堆实现的优先级队列
   Rank s = 2*n/3; Rank* A = new Rank[s]; //创建容量为2*n/3的数组，且
   for ( Rank i = 0; i < s; i++ ) A[i] = dice( 3*n ); //所有词条随机
   printf( "Creating a heap of size %d from %d random keys:\n", n/3, s );
   for ( Rank i = 0; i < s; i++ ) print( A[i] ); printf( "\n" );
   PQ heap( A + n/6, n/3 ); delete [] A; //批量建堆（PQ_ComplHeap实现了Robert Floyd算法）
   print( heap );
   while ( heap.size() < n ) { //随机测试
      if ( dice( (Rank) 100 ) < 70 ) //70%概率插入新词条
         { Rank e = dice( 3*n ); printf( "insert(" ); print( e ); printf( ")\n" ); heap.insert( e ); }
      else //30%概率摘除最大词条
         if ( !heap.empty() )
            { printf( "delMax() =" ); print( heap.delMax() ); printf( "\n" ); }
      print( heap );
   }
   while ( !heap.empty() ) //清空
      { printf( "delMax() =" ); print( heap.delMax() ); printf( "\n" ); }
   print( heap );
   while ( heap.size() < n/23 ) //随机插入
      { Rank e = dice( 3*n ); printf( "insert(" ); print( e ); printf( ")\n" ); heap.insert( e ); }
   print( heap );
   while ( !heap.empty() ) //再次清空
      { printf( "delMax() =" ); print( heap.delMax() ); printf( "\n" ); }
   print( heap );
}

int main( int argc, char* argv[] ) { //优先级队列测试
   if ( 2 > argc ) { printf( "Usage: %s <size of test>\a\a\n", argv[0] ); return 1; }
   //srand( (uint32_t) time(nullptr) ); //随机种子
   srand( 31415926 ); //固定种子（假种子，调试用）
#if defined(DSA_PQ_LEFTHEAP)
   testPq<PQ_LeftHeap<Rank>>( atoi( argv[1] ) ); //词条类型可以在这里任意选择
#elif defined(DSA_PQ_COMPLHEAP)
   testPq<PQ_ComplHeap<Rank>>( atoi( argv[1] ) ); //词条类型可以在这里任意选择
#elif defined(DSA_PQ_LIST)
   testPq<PQ_List<Rank>>( atoi( argv[1] ) ); //词条类型可以在这里任意选择
#else
   printf( "Unrecognized PQ type\n" );
#endif
   return 0;
}
