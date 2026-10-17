#pragma once

template <typename T> BNP<T> RedBlack<T>::insert( const T& e ) {
   BST::insert( e, 1 ); //先按BST规则插入_x（黑高度为1）并染红（祖先黑高度不变），则
   if ( _p != _x ) solveDoubleRed(); //条件1、2、4依然满足，但3未必，或需做双红修正
   return _x; //无论原树中是否存有e，返回时总有_x->data == e
} //insert
