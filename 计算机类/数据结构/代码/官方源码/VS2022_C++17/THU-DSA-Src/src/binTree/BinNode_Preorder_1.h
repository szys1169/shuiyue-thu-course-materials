#pragma once

template <typename T, typename V> void preorder1( BNP<T> x, V& visit ) {
   Stack<BNP<T>> S; S.push( x ); //从当前节点出发
   while ( !S.empty() ) //以右子树为单位，依次访问每一条藤
      for ( x = S.pop(); x; x = x->lc ) //自x出发，沿着藤依次
         { visit( x->data ); S.push( x->rc ); } //访问各节点，并令右孩子（或空）入栈
} //preorder1
