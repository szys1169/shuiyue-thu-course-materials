#pragma once

template <typename T> bool BTree<T>::remove( const T& e ) {
   BTNP<T> x = search( e ); Rank k = x->key.search( e );
   if ( e != x->key[k] ) return false; //确认e的确存在
   if ( x->child[0] ) { //即便x不是叶子，亦可经过如下的腾挪，使之“成为”叶子
      BTNP<T> s = x->child[k+1]; //在右子树中一路向左，末端叶节点s中的首个关键码
      while ( s->child[0] ) s = s->child[0]; //就是e的后继
      x->key[k] = s->key[0]; x = s; k = 0; //令e与之交换
   } //至此，x必是叶节点，且e“是”其中的第k个关键码
   x->key.remove( k ); x->child.remove(); _size--; //删除e以及其下的一个外部节点
   solveUnderflow( x ); //如下溢，则修复之
   return true;
} //remove
