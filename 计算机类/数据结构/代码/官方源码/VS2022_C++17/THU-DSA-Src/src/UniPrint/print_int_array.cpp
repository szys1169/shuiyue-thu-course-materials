#include <cstdio>

void print( int A[], int n, int lo, int hi ) { //输出整数数组区间A[lo, hi)
   bool sorted = true;
   for ( int i = 1; i < n; i++ ) if ( A[i-1] > A[i] ) sorted = false;
   printf( sorted ? "S : " : "U : " );
   for ( int i = 0; i < lo; i++ ) printf( "   ." );
   for ( int i = lo; i < hi; i++ ) printf( "%4d", A[i] );
   for ( int i = hi; i < n; i++ ) printf( "   ." );
   printf( "\n" );
}

void print( int A[], int n ) { print( A, n, 0, n ); }
