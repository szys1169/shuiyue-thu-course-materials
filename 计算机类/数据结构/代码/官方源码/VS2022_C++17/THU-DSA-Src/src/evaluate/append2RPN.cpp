/*DSA*/#include "evaluate.h"

void append( char* rpn, double opnd ) { //将操作数接至RPN末尾
   char buf[64];
   if ( ( int ) opnd < opnd ) sprintf( buf, "%6.2f \0", opnd ); //浮点格式，或
   else                       sprintf( buf, "%d \0",( int ) opnd ); //整数格式
   strcat( rpn, buf ); //RPN加长
}

void append( char* rpn, char optr ) { //将运算符接至RPN末尾
   int n = strlen( rpn ); //RPN当前长度（以'\0'结尾，长度n + 1）
   sprintf( rpn + n, "%c \0", optr ); //接入指定的运算符
}
