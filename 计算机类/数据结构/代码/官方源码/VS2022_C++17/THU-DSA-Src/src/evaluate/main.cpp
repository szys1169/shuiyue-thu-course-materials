/*DSA*/#include "evaluate.h"

char* removeSpace( char* s ) { //剔除s[]中的白空格
   for ( char *p = s-1, *q = s; (p < s) || *p; *++p = *q++ )
      while ( isspace( *q ) ) q++;
   return s;
}

int main( int argc, char* argv[] ) { //表达式求值（入口）
   for ( int i = 1; i < argc; i++ ) { //逐一处理各命令行参数（表达式）
      /*DSA*/system( "cls" );
      char* rpn = new char[strlen( argv[i] )*4];   rpn[0] = '\0'; //逆波兰表达式（4倍原串长，通常不致溢出）
      double value = evaluate( removeSpace( argv[i] ), rpn ); //求值
      /*DSA*/printf( "EXPR\t: %s\n", argv[i] ); //输出原表达式
      /*DSA*/printf( "RPN\t: [ %s]\n", rpn ); //输出RPN
      /*DSA*/printf( "Value\t= %f = %d\n\n", value,( int ) round(value) ); //输出表达式的值
      delete rpn;
      /*DSA*/getchar();
   }
   return 0;
}
