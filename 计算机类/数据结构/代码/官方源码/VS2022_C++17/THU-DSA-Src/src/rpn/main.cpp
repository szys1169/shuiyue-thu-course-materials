/*DSA*/#include "rpn.h"

int main( int argc, char* argv[] ) { //RPN求值（入口）
   for ( int i = 1; i < argc; i++ ) { //逐一处理各命令行参数（表达式）
      system( "cls" );
      char* RPN = strdup( argv[i] );
      printf( "[ %s ] x%d\n", RPN, strlen( RPN ) );
      double value = rpn( RPN ); //求值
      printf( "Value = %f = %d\n", value, (int) round(value) ); //输出表达式的值
      free( RPN );
      getchar();
   }
   return 0;
}
