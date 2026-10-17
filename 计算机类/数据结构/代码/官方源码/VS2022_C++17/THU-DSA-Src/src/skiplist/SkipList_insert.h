#pragma once

template <typename T> TowerPosi<T> Skiplist<T>::insert( const T& e ) {
   search( e ); if ( (_x != head) && (e == key(_x)) ) return _x; //禁止重复
   TowerPosi<T> pred = _x, succ = _x->succ; //同层的前驱（或为head）、后继（或为tail）
   _x = List::insert( _x, Tower<T>( e ) ); //紧邻于_x之右侧，创建一座空塔
   for ( Rank h = 0; !h || (rand()&1); h++ ) { //积砖成塔（至少一层）
      if ( height(head) < h+1 ) { //若总高度不足h，则需创建一层（仅含两个哨兵）
         tower(head).insert( Brick<T>( nullptr, tail ) );
         tower(tail).insert( Brick<T>( head, nullptr ) );
      }
      while ( height( pred ) == h )
         pred = tower( pred )[h - 1].pred; //踏过若干塔顶，找到左邻
      while ( height( succ ) == h )
         succ = tower( succ )[h - 1].succ; //踏过若干塔顶，找到右邻
      tower( _x ).insert( Brick<T>( pred, succ ) ); //新塔长高一层
      tower( pred )[h].succ = tower( succ )[h].pred = _x; //左右连接
   } //for
   return _x; //返回新塔
} //insert
