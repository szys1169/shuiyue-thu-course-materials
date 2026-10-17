#pragma once

template <typename T> Rank clean( BNP<T> x ) { //析构子树x
   if ( !x ) return 0;
   Rank n = 1 + clean( x->lc ) + clean( x->rc ); //递归析构左、右子树
   delete x; return n;
} //clean

template <typename T> Rank BinTree<T>::remove( BNP<T> x ) { //删除子树x
   if ( !x ) return 0;
   FromParentTo( x ) = nullptr; //切断来自父节点的引用
   if ( x->parent ) x->parent->updateHeightAbove(); //更新祖先们的高度
   Rank n = clean( x ); _size -= n; return n; //析构子树x
} //remove
