#pragma once

#define HeightUpdated(x) /* 常规BST高度更新条件 */ \
   ( (x)->height == 1 + max( Height( (x)->lc ), Height( (x)->rc ) ) )

//BinTree节点
template <typename T> void UniPrint::p( BNP<T> node ) {
   p( node->data ); //数值
   printf( "(%2d)", node->height ); //高度、黑高度、NPL
   printf( //父子链接指针
 ( node->lc && node != node->lc->parent ) ||
 ( node->rc && node != node->rc->parent ) ?
      "@" : " "
   );
#if defined(DSA_REDBLACK)
   printf( node->color ? "B" : " " ); //节点颜色（忽略红节点）
#endif

//父子（黑）高度、NPL匹配
#if   defined(DSA_PQ_COMPLHEAP)
   //高度不必匹配
#elif defined(DSA_PQ_LEFTHEAP)
   printf( //NPL
 ( node->rc && ( node->npl != 1 + node->rc->npl ) ) ||
 ( node->lc && ( node->npl >  1 + node->lc->npl ) ) ?
      "%%" : " "
   );
#elif defined(DSA_REDBLACK)
   printf( RbtBalanced( node ) ? " " : "!" ); //黑高度
#else
   printf( HeightUpdated( node ) ? " " : "!" ); //（常规）高度
#endif

//左右平衡
#if defined(DSA_AVL)
   if ( !AvlBalanced( node ) ) printf( "X" ); //AVL失衡
   else if ( 0 < BalFac( node ) ) printf( "\\" ); //左偏
   else if ( BalFac( node ) < 0 ) printf( "/" ); //右偏
   else printf( "-" ); //AVL平衡
#elif defined(DSA_REDBLACK)
   int hL = node->lc ? node->lc->height + node->lc->color : 1;
   int hR = node->rc ? node->rc->height + node->rc->color : 1;
   if ( hL > hR ) printf( "/" ); //左偏
   else if ( hL < hR ) printf( "/" ); //右偏
   else printf( "-" ); //RB平衡
#else
   //平衡无所谓
#endif
}
