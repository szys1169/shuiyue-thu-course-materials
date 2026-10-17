#pragma once

template <typename T> bool Skiplist<T>::remove( const T& e ) {
   search( e ); if ( (_x == head) || (e != key(_x)) ) return false; //若不存在，直接返回
   for ( Rank h = height(_x) - 1; -1 != h; h-- ) { //自顶而下，逐层拆塔
      Brick<T>& b = tower(_x)[h];
      tower(b.pred)[h].succ = b.succ; tower(b.succ)[h].pred = b.pred;
      if ( head == b.pred && b.succ == tail ) //及时清除空层
         { tower(head).remove(h); tower(tail).remove(h); }
   }
   List::remove( _x ); return true; //删除成功
} //remove
