#pragma once

template <typename T> //合并以a和b为根节点的两个左式堆（迭代版）
BNP<T> merge( BNP<T> a, BNP<T> b ) {
   if ( !a ) return b; //退化情况
   if ( !b ) return a; //退化情况
   if ( *a < *b ) swap( a, b ); //确保a>=b
   for ( ; a->rc; a = a->rc ) //沿右侧链做二路归并，直至堆a->rc先于b变空
      if ( *(a->rc) < *b ) //只有在a->rc < b时才需做实质的操作
         { b->parent = a; swap( a->rc, b ); } //接入b的根节点（及其左子堆）
   ( a->rc = b )->parent = a; //直接接入b的残余部分（必然非空）
   for ( ; a; a->npl = NPL(a->rc) + 1, b = a, a = a->parent ) //沿右侧链逐层回溯、更新npl
      if ( NPL(a->lc) < NPL(a->rc) ) //若有必要（宏隐藏了边界情况）
         swap( a->lc, a->rc ); //通过交换确保右子堆的npl不大
   return b; //返回合并后的堆顶
} //本算法只实现结构上的合并，堆的规模须由上层调用者负责更新
