#pragma once

template <typename T, typename V> void inorder1( BNP<T> x, V& visit ) {
   Stack<BNP<T>> S;
   while ( x || !S.empty() ) { //只要x非nullptr，或S仍非空
      for ( ; x; x = x->lc ) S.push( x ); //藤上节点便自顶而下入栈
      visit( ( x = S.pop() )->data );  x = x->rc; //取出并访问栈顶节点，再转向右子树
   } //while
} //inorder1
