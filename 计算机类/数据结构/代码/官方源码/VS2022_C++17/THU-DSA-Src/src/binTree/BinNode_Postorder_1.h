#pragma once

/*DSA*/#include "stack/Stack.h"

template <typename T> void gotoLeftmostLeaf( Stack<BNP<T>>& S ) {
   for ( BNP<T> x = S.top(); x;  ) { //自顶而下，反复考查当前节点
      if ( x->rc ) S.push( x->rc ); //右孩子优先入栈
      if ( x->lc ) { S.push( x->lc ); x = x->lc; } //若有左孩子，则优先左转
      else x = x->rc; //实不得已，才向右
   } //for
} //gotoLeftmostLeaf
template <typename T, typename V> void postorder1( BNP<T> x, V& visit ) {
   Stack<BNP<T>> S; if ( x ) S.push( x ); //辅助栈
   while ( !S.empty() ) { //x始终为当前节点
      if ( S.top() != x->parent ) //若栈顶非x之父（而为右兄）
         gotoLeftmostLeaf( S ); //则在右兄子树中理出对应的藤
      x = S.pop(); visit( x->data ); //弹出并访问栈顶（即前一节点之后继）
   } //while
} //postorder1
