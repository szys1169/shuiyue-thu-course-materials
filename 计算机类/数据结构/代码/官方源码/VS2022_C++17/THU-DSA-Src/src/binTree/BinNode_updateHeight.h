#pragma once

#define Height( x ) ( ( x ) ? ( x )->height : -1 ) //简化描述（空树高度为-1）

template <typename T> int BinNode<T>::updateHeight() //更新当前节点高度
   { return height = 1 + max( Height( lc ), Height( rc ) ); }
template <typename T> void BinNode<T>::updateHeightAbove() //更新当前节点及其祖先的高度
   { for ( BNP<T> x = this; x; x = x->parent ) x->updateHeight(); } //可优化
