#include "list_test.h"

Rank testID = 0; //测试编号

template <typename T> //随机生成长度为n的列表（其中可能包含重复节点）
void randomList( List<T>& list, Rank n ) { //创建长度为n的列表，其元素随机取自[0, 4n)
   LNP<T> p = ( rand() % 2 )
         ? list.insertLast( rand() %( T ) ( n* 4 ) )
         : list.insertFirst( rand() %( T ) ( n* 4 ) );
   for ( Rank i = 1; i < n; i++ )
      p = rand() % 2
         ? list.insert( rand() %( T ) ( n* 4 ), p )
         : list.insert( p, rand() %( T ) ( n* 4 ) );
}

template <typename T> void testList( Rank testSize ) { //测试列表
   printf("\n  ==== Test %2d. Generate a random list with %d elements\n", testID++, testSize);
   List<T> L; randomList(L, testSize); PRINT(L);
//
   printf("\n  ==== Test %2d. sort intervals\n", testID++);
   Rank d = 1 + testSize / 5;
   for ( Rank k = 0; k < 5; k++ ) {
      Rank h = k*d, t = 1 + min<Rank>((k+1)*d, testSize);
      printf( "(%d,%d) Sorted\n", h-1, t-1 );
      L.sort( *(L.first()->pred) + h, *(L.first()->pred) + t ); PRINT(L);
   }
//
   printf("\n  ==== Test %2d. Sort all\n", testID++);
   L.sort(); PRINT(L);
//
   printf("\n  ==== Test %2d. Generate two sorted lists each with %d random elements\n", testID++, testSize);
   List<T> Lx; randomList(Lx, testSize); PRINT(Lx); Lx.sort(); PRINT(Lx);
   List<T> Ly; randomList(Ly, testSize); PRINT(Ly); Ly.sort(); PRINT(Ly);
//
   printf("\n  ==== Test %2d. Join them\n", testID++);
   LNP<T> q = Lx.join( Ly ); PRINT(Lx); PRINT(Ly);
//
   printf("\n  ==== Test %2d. Merge them\n", testID++);
   if ( q ) Lx.merge( q ); PRINT(Lx); PRINT(Ly);
//
   printf( "\n  ==== Test %2d. Generate two lists each of size %d by random insertions\n", testID++, testSize );
   List<T> La; randomList( La, testSize ); PRINT( La );
   List<T> Lb; randomList( Lb, testSize ); PRINT( Lb );
//
   printf( "\n  ==== Test %2d. Call list members by Rank(with high complexity)\n", testID++ );
   for ( Rank i = 0; i < La.size(); i++ ) print( La[i]->data ); printf( "\n" );
   for ( Rank i = 0; i < Lb.size(); i++ ) print( Lb[i]->data ); printf( "\n" );
//
   printf( "\n  ==== Test %2d. Concatenation\n", testID++ ); PRINT( La ); PRINT( Lb );
   while ( 0 < Lb.size() ) La.insertLast( Lb.remove( Lb.first() ) ); PRINT( La ); PRINT( Lb );
//
   printf( "\n  ==== Test %2d. Increase\n", testID++ ); PRINT( La );
   increase( La ); PRINT( La );
//
   printf( "\n  ==== Test %2d. Lowpass(with high complexity) on\n", testID++ ); PRINT( La );
   Rank i = La.size(); while ( 0 < --i ) { La[i-1]->data += La[i]->data; La[i-1]->data >>= 1; } PRINT( La ); //call-by-rank, clear but slow
//
   printf( "\n  ==== Test %2d. reverse\n", testID++ );
   La.reverse(); PRINT( La );
//
   printf( "\n  ==== Test %2d. Copy all\n", testID++ ); PRINT( La );
   List<T> Le( La ); PRINT( Le );
   Rank r = dice( La.size() / 4 ), n = dice( La.size()* 3 / 4, La.size() ) - r;
//
   printf( "\n  ==== Test %2d. Copy [%d, %d)\n", testID++, r, r + n );
   List<T> Ld( La, r, n ); PRINT( Ld );
//
   printf( "\n  ==== Test %2d. Trim by random deletions\n", testID++ ); PRINT( Ld );
   while ( testSize / 4 < Ld.size() ) {
      Rank N = dice( Ld.size() ); printf( "remove(L[%d] =", N );
      LNP<T> p = Ld[N]; print( p->data ); printf( ")\n" ); //call-by-rank, clear but slow
      Ld.remove( p ); PRINT( Ld );
   }
//
   printf( "\n  ==== Test %2d. Copy\n", testID++ ); PRINT( La );
   List<T> Lf( La ); PRINT( Lf );
//
   printf( "\n  ==== Test %2d. FIND in\n", testID++ ); PRINT( Lf );
   for ( Rank i = 0; i <= testSize* 2; i++ ) { //逐一测试[0, 2n]中的所有可能
      LNP<T> p = Lf.find( ( T ) i ); printf( "find(" ); print( ( T ) i ); printf( "):\t" );
      if ( p ) print( p->data );
      else printf( "nullptr" );
      printf( "\n" );
   } //正确的结构应该是大致（n+1次）失败、（n次）成功相间
//
   printf( "\n  ==== Test %2d. Sort\n", testID++ ); PRINT( La );
   La.sort(); PRINT( La );
//
   printf( "\n  ==== Test %2d. SEARCH in\n", testID++ ); PRINT( La );
   for ( Rank i = 0; i <= testSize* 2; i++ ) { //逐一测试[0, 2n]中的所有可能
      LNP<T> p = La.search( ( T ) i ); printf( "search(" ); print( ( T ) i ); printf( "):\t" );
      p->pred ? print( p->data ) : print( "head" );
      printf( ( p->pred && ( (T)i == p->data ) ) ? "\tO\n" : "\tX\n" );
   } //正确的结构应该是大致（n+1次）失败、（n次）成功相间
//
   printf( "\n  ==== Test %2d. Remove redundancy in\n", testID++ ); PRINT( La );
   Rank oldSize = La.size(); La.uniquify();
   printf( "%d node(s) removed\n", oldSize - La.size() ); PRINT( La ); La.reverse(); PRINT( La );
//
   printf( "\n  ==== Test %2d. Remove redundancy in\n", testID++ ); PRINT( Le );
   oldSize = Le.size(); Le.dedup();
   printf( "%d node(s) removed\n", oldSize - Le.size() ); PRINT( Le );
//
   printf( "\n  ==== Test %2d. Sort\n", testID++ ); PRINT( Le );
   Le.sort(); PRINT( Le );
//
   return;
}

int main( int argc, char* argv[] ) { //测试列表
   if ( 2 > argc ) { printf( "Usage: %s <size of test>\a\a\n", argv[0] ); return 1; }
   //srand( (uint32_t) time(nullptr) ); //随机种子
   srand( 31415926 ); //固定种子（假种子，调试用）
   testList<int>( atoi( argv[1] ) ); //元素类型可在此指定
   return 0;
}
