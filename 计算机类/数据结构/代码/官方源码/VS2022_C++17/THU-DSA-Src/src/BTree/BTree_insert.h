#pragma once

template <typename T> bool BTree<T>::insert( const T& e ) {
   BTNP<T> x = search( e ); Rank k = x->key.search( e );
   if ( e == x->key[k] ) return false; //确认e尚不存在，即x为叶节点
   x->key.insert( k+1, e ); //e作为第k+1个关键码，插至x中
   x->child.insert( nullptr ); //相应地，其下增加一个外部节点
   _size++; solveOverflow( x ); //如上溢，则修复之
   return true; //插入成功
} //insert
