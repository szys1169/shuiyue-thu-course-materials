#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "_share/util.h"
#include "UniPrint/print.h"
#include "vector/vector.h"
#include "factorial/fac.h"

/******************************************************************************************
 * 排序算法完全测试
 ******************************************************************************************/
void test( Vector<Rank>& A, Rank n ) {
   if ( n < 2 )
      printf("\n");
   else
      for ( Rank i = 0; i < n; i++ ) {
         print(A);
         test( A, n-1 );
         swap( A[n % 2 ? 0 : i], A[n-1] );
      }
}

void sorterTest( Rank n ) {
   Vector<Rank> A(n);
   for ( Rank i = 0; i < n; i++ ) A.insert( i );
   test( A, n );
}

int main( int argc, char* argv[] ) {
   if ( 2 > argc ) { printf( "Usage:\n\t%s <sequence length> \a\a\n", argv[0] ); return 1; }
   srand( (unsigned int)time( NULL ) ); //随机种子
   //srand( 31415926 ); //固定种子（假种子，调试用）
   int tests = abs( atoi( argv[1] ) );
   printf( "test length = %d\n", tests );
   sorterTest( tests );
   return 0;
}
