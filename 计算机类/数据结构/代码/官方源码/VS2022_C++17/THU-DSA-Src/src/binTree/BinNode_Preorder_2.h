#pragma once

template <typename T, typename V>
void preorder2( BNP<T> x, V& visit ) {
   Stack<BNP<T>> S; //辅助栈
   if ( x ) S.push( x ); //根节点入栈
   while ( !S.empty() ) { //在栈变空之前反复循环
      x = S.pop(); visit( x->data ); //弹出并访问当前节点，其非空孩子的入栈次序为先右后左
      if ( x->rc ) S.push( x->rc );
      if ( x->lc ) S.push( x->lc );
   }
} //preorder2
