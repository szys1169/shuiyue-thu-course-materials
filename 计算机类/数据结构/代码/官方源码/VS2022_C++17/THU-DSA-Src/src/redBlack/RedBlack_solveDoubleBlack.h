#pragma once

/******************************************************************************************
 * RedBlack双黑调整算法：解决节点x与被其替代的节点均为黑色的问题
 * 分为三大类共四种情况：
 *    BB-1 ：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
 *    BB-2R：2次颜色翻转，2次黑高度更新，0次旋转，不再递归
 *    BB-2B：1次颜色翻转，1次黑高度更新，0次旋转，需要递归
 *    BB-3 ：2次颜色翻转，2次黑高度更新，1次旋转，转为BB-1或BB2R
 ******************************************************************************************/
template <typename T> void RedBlack<T>::solveDoubleBlack() {
   while ( _p ) {
      BNP<T> s = ( _r == _p->lc ) ? _p->rc : _p->lc; //_r（或为nullptr）的兄弟s（必非nullptr）
      if ( IsBlack( s ) ) //兄弟s为黑
         if ( IsRed( s->lc ) || IsRed( s->rc ) ) { //黑s有红孩子：BB-1
            BNP<T> b = rotate( _p ); //沿_p、s、t旋转后，新根继承原根的
            b->color = _p->color; b->height = _p->height + 1; //颜色和黑高度
            b->lc->color = b->rc->color = RBT_BLACK; //左子、右子（均必非nullptr）染黑
            break; //一蹴而就
         } else { //黑s无红孩子
            s->color = RBT_RED; _p->height--; //s转红，_p坍塌一层
            if ( IsRed( _p ) ) { _p->color = RBT_BLACK; break; } //BB-2R：_p转黑，黑高度不变
            else { _r = _p; _p = _r->parent; } //BB-2B：黑_p的黑高度下降，继续上溯
         } //else
      else { //兄弟s为红：BB-3
         s->color = RBT_BLACK; _p->color = RBT_RED; //s转黑，_p转红
         rotate( _p ); //沿_p、s、t旋转（接下来只能是BB-1或BB-2R）后，继续上溯
      } //else
   } //while
} //solveDoubleBlack
