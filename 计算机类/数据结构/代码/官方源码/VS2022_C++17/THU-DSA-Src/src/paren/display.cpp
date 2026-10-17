#include "paren.h"

void displaySubstring( const char A[], Rank lo, Rank hi ) { //显示表达式片段[lo,hi]，与原表达式对齐
   for ( Rank i = 0; i < lo; i++ ) printf( " " );
   for ( Rank i = lo; i <= hi; i++ ) printf( "%c", A[i] );
   printf( "\n" );
}

void displayProgress( const char A[], Rank i, Stack<char> S ) { //显示表达式扫描进度
   printf( "\n%s\n", A ); for ( Rank j = 0; j < i; j++ )   printf( "-" );
   printf( "^\n" ); print( S ); getchar();
}
