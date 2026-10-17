/*DSA*/#include "rpn.h"

double rpn( char* S ) { //对RPN求值
   Stack<double> opnd; //仅需一个运算数栈
   for ( char* item = strtok( S, " " ); item; item = strtok( nullptr, " ") )
   /*DSA*/ {
      /*DSA*/printf( "\n[%s]\n", item );
      if ( 1 < strlen( item ) || isdigit( item[0] ) ) //遇到操作数
         opnd.push( atof( item ) ); //则令其入栈
      else //遇到运算符
         opnd.push( calcu( opnd, item[0] ) ); //则直接计算
      /*DSA*/print( opnd );
   /*DSA*/}//for
   return opnd.pop(); //唯一尚存的操作数，即为计算结果
} //rpn
