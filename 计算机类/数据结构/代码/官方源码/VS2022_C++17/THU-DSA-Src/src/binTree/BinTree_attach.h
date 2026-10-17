#pragma once

/*DSA*/template <typename T> //将S当作节点x的左子树接入，再将S置空
/*DSA*/BNP<T> BinTree<T>::attach( BinTree<T> S, BNP<T> x ) { //x->lc == nullptr
/*DSA*/   if ( ! ( x->lc = S._root ) ) return nullptr; //空树无需费事
/*DSA*/   x->lc->parent = x; //接入
/*DSA*/   _size += S._size; x->updateHeightAbove(); //更新全树规模与x所有祖先的高度
/*DSA*/   S._root = nullptr; S._size = 0; return x; //释放原树，返回接入位置
/*DSA*/} //右子树的接入完全对称，请自行补充
/*DSA*/
template <typename T> //将S当作节点x的右子树接入，再将S置空
BNP<T> BinTree<T>::attach( BNP<T> x, BinTree<T> S ) { //x->rc == nullptr
   if ( ! ( x->rc = S._root ) ) return nullptr; //空树无需费事
   x->rc->parent = x; //接入
   _size += S._size; x->updateHeightAbove(); //更新全树规模与x所有祖先的高度
   S._root = nullptr; S._size = 0; return x; //释放原树，返回接入位置
} //左子树的接入完全对称，请自行补充
