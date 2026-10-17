#pragma once

template <typename T, bool H> bool BST<T, H>::remove( const T& e ) {
   search( e ); if ( !_x ) return false; //确认目标存在（留意_p的设置）
   if ( _x->lc && _x->rc ) { //双子情况，可转化为单子情况...
      BNP<T> s = eov(_x->rc); swap( _x->data, s->data ); //直接后继，s代_x僵
      _x = s; _p = s->parent; //转移删除操作的焦点
   } //以下，_x至多只有一个孩子
   _r = _x->lc ? _x->lc : _x->rc; //以单子r为接替者（仍可能是nullptr）
   if ( _r ) _r->parent = _p; //_r以_p为父
   ( _p ? ( _p->lc == _x ? _p->lc : _p->rc ) : _root ) = _r; //_p以_r为子
   delete _x; _x = nullptr; _size--; //释放_x，更新全树规模
   if ( H && _p ) //更新祖先们的高度
      _p->updateHeightAbove(); //派生的AVL树、红黑树会重写insert()，并以自己的方式更新高度
   return true;
} //删除成功与否，由返回值指示
