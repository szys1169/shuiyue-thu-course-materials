/*DSA*/#include "evaluate.h"

double calcu( Stack<double>& opnd, char op ) {
   if ( '!' == op ) // 一元运算
      return (double) facI( (int) opnd.pop() );
   double b = opnd.pop(), a = opnd.pop(); //二元运算
   switch( op ) {
      case '+' : return a + b;
      case '-' : return a - b;
      case '*' : return a * b;
      case '/' : if ( 0 == b ) exit( -1 ); return a/b; //如此判浮点数为零并不可靠
      case '^' : return pow( a, b );
      default  : exit( -1 );
   } //switch
} //calcu
