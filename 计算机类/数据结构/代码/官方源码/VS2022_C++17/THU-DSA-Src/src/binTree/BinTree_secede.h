#pragma once

template <typename T> BinTree<T> BinTree<T>::secede( BNP<T> x ) { //子树分离
   FromParentTo( x ) = nullptr; //切断来自父节点的指针
   if ( x->parent ) x->parent->updateHeightAbove(); //更新原祖先们的高度
   BinTree<T> S; S._root = x; x->parent = nullptr; //新树以x为根
   S._size = x->size(); _size -= S._size; return S; //更新规模，返回子树
} //secede
