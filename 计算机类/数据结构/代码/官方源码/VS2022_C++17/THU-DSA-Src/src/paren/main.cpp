#include   "paren.h"

int main( int argc, char* argv[] ) { //检查表达式括号是否匹配
//检查参数
   if ( 2 > argc ) { //至少要提供一个待检查的字符串
      fprintf( stderr, "\nUsage: %s <string#1> <string#2> ... \n", argv[0] );
      fprintf( stderr, "For example %s(a[i-1][j+1])+a[i+1][j-1])*2\n", argv[0] );
      return -1;
   }
//逐一检查各串是否匹配
   for ( int i = 1; i < argc; i++ ) {
      char* s = argv[i];
      paren( s, strlen( s ) ) ?
         printf( "\n%s: 匹配\n", s ) :
         printf( "\n%s: 不匹配\n", s );
      getchar();
   }
   return 0;
}
