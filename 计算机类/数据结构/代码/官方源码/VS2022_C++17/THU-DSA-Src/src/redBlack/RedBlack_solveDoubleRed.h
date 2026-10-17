#pragma once

/******************************************************************************************
 * RedBlack双红调整算法：解决节点x与其父均为红色的问题。分为两大类情况：
 *    RR-1：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
 *    RR-2：3次颜色翻转，3次黑高度更新，0次旋转，需要递归
 ******************************************************************************************/
template <typename T> void RedBlack<T>::solveDoubleRed() {
   for ( BNP<T> x = _x; ; ) {
      if ( !x->parent ) //若已（递归）转至树根，则将其转黑，整树黑高度也随之递增
         {  x->color = RBT_BLACK; break;  } //否则，x的父亲p必存在
      BNP<T> p = x->parent; if ( IsBlack( p ) ) break; //若p为黑，则可终止调整
      BNP<T> g = p->parent; //否则x的祖父必存在且为黑
      BNP<T> u = Uncle( x ); //以下，视x叔父的颜色分别处理
      if ( IsBlack( u ) ) { //RR-1：u为黑（含nullptr）
         BNP<T> b = rotate( g ); b->color = RBT_BLACK; //绕g旋转后，根节点染黑
         b->lc->color = b->rc->color = RBT_RED; break; //孩子们染红，即完成修复
      } else { //RR-2：u为红
         p->color = u->color = RBT_BLACK; //p、u由红转黑
         g->color = RBT_RED; g->height++; //在B-树中g是上交的关键码，故染红
         x = g; //继续上溯
      } //else
   } //for
} //solveDoubleRed
