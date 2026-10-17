/*DSA*/#include "evaluate.h"

double evaluate( char* S, char* RPN ) { //对表达式S求值，并转换为RPN
   Stack<double> opnd; Stack<char> optr; //运算数栈、运算符栈
   /*DSA*/ char* expr = S;
   for ( optr.push('\0'); !optr.empty(); ) //哨兵'\0'入栈，然后顺序扫描
      /*DSA*/ {
      if ( isdigit( *S ) ) //遇到操作数，则读入，并续接至RPN
         { readNumber( S, opnd ); append( RPN, opnd.top() ); }
      else //若遇到运算符，则视其与栈顶运算符之相对优先级
         switch( prio( optr.top(), *S ) ) { //分别处理
            case '<': //栈顶运算符优先级更低时
               optr.push( *S ); S++; //计算推迟，当前运算符进栈
               break;
            case '>': //反之
               append( RPN, optr.top() ); //栈顶运算符续接至RPN
               opnd.push( calcu( opnd, optr.pop() ) ); //实施计算，结果入栈（calcu()自行实现）
               break;
            case '~': //括号或哨兵'\0'
               optr.pop(); S++; //脱括号并转至下一字符
               break;
            /*DSA*/default: exit( -1 ); //逢语法错误，直接退出
         } //switch
      /*DSA*/displayProgress( expr, S, opnd, optr, RPN );
      /*DSA*/}//for
   return opnd.pop(); //唯一尚存的操作数，即为计算结果
} //evaluate：请自行扩充该算法，使之可以识别并处理非法的表达式
