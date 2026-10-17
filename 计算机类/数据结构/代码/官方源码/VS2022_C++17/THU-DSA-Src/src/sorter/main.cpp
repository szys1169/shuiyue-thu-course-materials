#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "_share/util.h"
#include "UniPrint/print.h"
#include "vector/vector.h"
#include "factorial/fac.h"

uint64_t passed = 0;
uint64_t done = 0;
uint64_t all = 0;

int test( Vector<Rank>& A, Rank n ) { //排序算法完全测试
   if ( n < 2 ) {
      print(A); Vector<Rank> X(A); X.sort(); print(X); printf("\n");
      for ( Rank i = 0; i < X.size(); i++ )
         if ( X[i] != i/2 ) { print(X); return 1; }
      passed++;
      if ( ( (passed - done) > 999999 ) || ( (passed - done)*20 > all ) )
         { printf( "%.1f%% : %I64d / %I64d\n", 100.*passed/all, passed, all ); done = passed; }
      return 0;
   }
   for ( Rank i = 0; i < n; i++ ) {
      if ( test( A, n-1 ) ) return 1;
      swap( A[n % 2 ? 0 : i], A[n-1] );
   }
   return 0;
}

int sorterTest( Rank n ) {
   Vector<Rank> A(n);
   for ( Rank i = 0; i < n; i++ ) A.insert( i/2 ); print( A ); printf("\n");
   return test( A, n );
}

int main( int argc, char* argv[] ) {
   if ( 2 > argc ) { printf( "Usage:\n\t%s <sequence length> \a\a\n", argv[0] ); return 1; }
   srand( (uint32_t) time(nullptr) ); //随机种子
   //srand( 31415926 ); //固定种子（假种子，调试用）
   int tests = abs( atoi( argv[1] ) );
   printf( "test length = %d\n", tests );
   all = facI( tests );
   sorterTest( tests ); printf( "%I64d / %I64d passed\n", passed, all );
   return 0;
}
