#pragma once

template <typename T> bool RedBlack<T>::remove( const T& e ) {
   if ( !BST::remove( e ) ) return false; //先按BST规则删除_p的孩子_x，接替者为_r
   if ( !RbtBalanced(_p) ) //若失衡（即原_x为黑）
      if ( IsRed(_r) ) //若接替者_r为红，则
         _r->color = RBT_BLACK; //只需令其继承_x的黑色，黑高度随即复原
      else //否则（即原_x及_r均为黑色）
         solveDoubleBlack(); //从_p出发，做双黑修正
   return true;
} //remove
