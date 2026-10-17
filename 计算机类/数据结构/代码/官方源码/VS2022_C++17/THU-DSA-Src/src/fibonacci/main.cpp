#include <ctime>
#include <iostream>
using namespace std;

#include "Fib.h"

uint64_t  fibI( int n ); //迭代版
#define  TABLE_SIZE 256
uint64_t  M[TABLE_SIZE]; //快查表
uint64_t  fibM( int n ); //记忆化版
uint64_t  fib( int n ); //二分递归版
uint64_t  fibL( int n, uint64_t& f ); //线性递归版

int main( int argc, char* argv[] ) { //测试FIB
//检查参数
   if ( 2 > argc ) { fprintf( stderr, "Usage: %s <Rank>\n", argv[0] ); return 1; }
   int n = atoi( argv[1] );
//依次计算Fibonacci数列各项
   printf( "\n------------- class Fib -------------\n" );
   Fib f( 0 );
   for ( int i = 0; i < n; i++, f.next() )
      printf( "fib(%2d) = %22I64d\n", i, f.get() );
   for ( int i = 0; i <= n; i++, f.prev() )
      printf( "fib(%2d) = %22I64d\n", n - i, f.get() );
   printf( "\n------------- Iteration -------------\n" );
   for ( int i = 0; i < n; i++ )
      printf( "fib(%2d) = %22I64d\n", i, fibI( i ) );
   printf( "\n------------- Linear Recursion -------------\n" );
   for ( int i = 0; i < n; i++ ) {
      uint64_t f;
      printf( "fib(%2d) = %22I64d\n", i, fibL( i, f ) );
   }
   printf( "\n------------- Memoization -------------\n" );
   memset( M, 0, sizeof( uint64_t )*TABLE_SIZE );
   for ( int i = 0; i < n; i++ )
      printf( "fib(%2d) = %22I64d\n", i, fibM( i ) );
   printf( "\n------------- Binary Recursion -------------\n" );
   for ( int i = 0; i < n; i++ )
      printf( "fib(%2d) = %22I64d\n", i, fib( i ) );
   return 0;
}
