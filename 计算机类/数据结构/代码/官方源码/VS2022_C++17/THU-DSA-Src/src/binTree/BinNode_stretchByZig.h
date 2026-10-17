#pragma once

//通过zig旋转调整，将BST子树x拉伸成最右侧通路
template <typename T> void stretchByZig( BNP<T>& x ) {
   if ( !x ) return;
   /*DSA*/int c = 0; //记录旋转次数
   BNP<T> r = x; while ( r->lc ) r = r->lc; //最小节点，必是子树最终的根
   BNP<T> v = x; while ( v->rc ) v = v->rc; //从最右侧通路的末端出发
   while ( v != r ) //逐层处理，直到抵达子树的根
      if ( v == v->zig() ) //以v为轴做zig旋转（同时更新高度）
         (v = v->parent)->updateHeight(); //直至没有左孩子
   /*DSA*/else
      /*DSA*/c++;
   x = r;
   /*DSA*/ printf( "size = %d, height = %d, #zig = %d\n", r->size(), r->height, c );
} //stretchByZig
