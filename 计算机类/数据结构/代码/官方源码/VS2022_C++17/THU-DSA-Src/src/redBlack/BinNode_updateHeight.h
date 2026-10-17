#pragma once


#define Height( x ) ( ( x ) ? ( x )->height : 0 ) //简化描述（空树黑高度为0）

template <typename T> int BinNode<T>::updateHeight() //更新节点高度
   { return height = max( HeightL(this), HeightR(this) ); } //孩子黑高度通常相等，除非出现双黑
   /*DSA*///红黑树中各节点左、右孩子的黑高度通常相等
   /*DSA*///在删除节点后的平衡调整过程中，如此方能正确地更新被删除节点父亲的黑高度
   /*DSA*///否则，rotateAt()会根据被删除节点的替代者（高度小一）设置父节点的黑高度
template <typename T> void BinNode<T>::updateHeightAbove() //更新当前节点及其祖先的高度
   { for ( BNP<T> x = this; x; x = x->parent ) x->updateHeight(); }
