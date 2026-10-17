/*DSA*/#include "sp.h"

Rank spCheck( Vector<Rank>& B ) { //B = unsort[1,n]
   Stack<Rank> S; Rank A = 1; //中转栈、输入栈，后者<1,2,3,...,n]只需记录栈顶
   for ( Rank n = B.size(), r = 0; r < n; S.pop(), r++ ) //模拟：逐项尝试B操作
      if ( S.empty() || S.top() != B[r] )
         if ( n < A  || B[r] < A ) //A已空，或者不含B[r]
         /*DSA*/{ print(S);
            return r; //卡住
         /*DSA*/}
         else
            do S.push( A++ ); //A操作
            while ( S.top() != B[r] );
   return B.size(); //成功
} //spCheck, O(n)
