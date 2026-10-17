#pragma once

//通过zag旋转调整，将BST子树x拉伸成最左侧通路
template <typename T> void stretchByZag( BNP<T>& x ) {
   if ( !x ) return;
   /*DSA*/int c = 0; //记录旋转次数
   BNP<T> r = x; while ( r->rc ) r = r->rc; //最大节点，必是子树最终的根
   BNP<T> v = x; while ( v->lc ) v = v->lc; //从最左侧通路的末端出发
   while ( v != r ) //逐层处理，直到抵达子树的根
      if ( v == v->zag() ) //以v为轴做zag旋转（同时更新高度）
         (v = v->parent)->updateHeight(); //直至没有右孩子
   /*DSA*/else
      /*DSA*/c++;
   x = r;
   /*DSA*/ printf( "size = %d, height = %d, #zag = %d\n", r->size(), r->height, c );
} //stretchByZag
