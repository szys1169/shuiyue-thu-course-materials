#pragma once

/*DSA*/template <typename T> void BinNode<T>::attachLc( BNP<T> x ) //接入左子树
/*DSA*/   { lc = x; if ( x ) x->parent = this; } //右子树的接入完全对称，请自行补充
/*DSA*/
template <typename T> void BinNode<T>::attachRc( BNP<T> x ) //接入右子树
   { rc = x; if ( x ) x->parent = this ; } //左子树的接入完全对称，请自行补充
