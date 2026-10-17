#pragma once

template <typename T> BNP<T> eov( BNP<T> x ) { //End Of Vine
   if ( x ) //从x出发
      for ( ; x->lc; x = x->lc ); //顺藤下行
   return x; //直至终点
} //eov
template <typename T> BNP<T> lla( BNP<T> x ) { //Lowest Left Ancestor
   while ( x->parent && x == x->parent->rc ) //右父亲的...右父亲的
      x = x->parent; //右父亲的
   return x->parent; //左父亲（可能是nullptr）
} //lla
template <typename T> BNP<T> BinNode<T>::succ() //中序后继
   { return rc ? eov(rc) : lla(this); } //若有右孩子，则是右子树中藤之终点；否则是最低左祖先
