#include "evaluate.h"
#include "UniPrint/print.h"

void printChar( char& p ) //输出运算符
{( '\0' == p ) ? printf( "\\0 " ) : printf( "%c  ", p ); }

void displayProgress( char* expr, char* pCh, Stack<double>& opndStk, Stack<char>& optrStk, char* rpn ) {
   printf( "\n" );
   for ( char* p = expr; '\0' != *p; p++ ) printf( " %c", *p ); printf( " $\n" );
   for ( char* p = expr; p < pCh; p++ ) printf( "  " );
   if ( '\0' != *( pCh - 1 ) )
      { for ( char* p = pCh; '\0' != *p; p++ ) printf( " %c", *p ); printf( " $" ); }
   printf( "\n" );
   for ( char* p = expr; p < pCh; p++ ) printf( "--" ); printf( " ^\n" );
   print( optrStk ); print( opndStk ); printf( "RPN:\n %s\n\n", rpn ); //输出RPN
}
