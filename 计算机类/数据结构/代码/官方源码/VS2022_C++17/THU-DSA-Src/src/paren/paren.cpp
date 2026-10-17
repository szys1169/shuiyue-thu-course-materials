/*DSA*/#include "paren.h"
/*DSA*/
bool paren( const char A[], Rank n ) {
   Stack<char> S; //记录已发现，但尚未匹配的左括号
   for ( Rank i = 0; i < n; i++ ) //一趟顺序扫描
   /*DSA*/{
      switch ( A[i] ) { //左括号无论何种，一律进栈；右括号必须与栈顶左括号同类
         case '(': case '[': case '{': S.push( A[i] ); break;
         case ')': if ( S.empty() || '(' != S.pop() ) return false; break;
         case ']': if ( S.empty() || '[' != S.pop() ) return false; break;
         case '}': if ( S.empty() || '{' != S.pop() ) return false; break;
      }
      /*DSA*/if ( '(' == A[i] || ')' == A[i] || '[' == A[i] || ']' == A[i] || '{' == A[i] || '}' == A[i] ) displayProgress( A, i, S );
   /*DSA*/}
   return S.empty(); //最终栈空，当且仅当匹配
} //paren, O(n)
