#pragma once

template <typename T, bool H> BNP<T> BST<T, H>::insert( const T& e, int h ) {
   if ( search( e ) ) return _p = _x; //有相等元素时，插入无效（用重复的_p和_x标记）
   _x = new BinNode<T>( e, _p, nullptr, nullptr, h ); //在_x处创建新节点，以_p为父
   ( _p ? ( *_x < *_p ? _p->lc : _p->rc ) : _root ) = _x; //_p以_x为子：左小右大
   if ( H && _p ) //更新祖先们的高度
      _p->updateHeightAbove(); //派生的AVL树、红黑树会重写insert()，并以自己的方式更新高度
   _size++; return _x; //新插入的节点，必为叶子
} //无论e此前是否存在，返回时总有_x->data == e
