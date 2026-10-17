#pragma once

template <typename T> BNP<T> Splay<T>::insert( const T& e ) { //将关键码e插入伸展树中
   if ( !_root ) { _size = 1; return _root = new BinNode<T>( e ); } //原树为空
   search( e ); if ( e == _root->data ) return _root; //查找成功（否则，_p已伸展至根）
   if ( _p->data < e ) //在右侧嫁接（rc或为空，lc == _p必非空）
      { _root = new BinNode<T>( e, nullptr, _p, _p->rc ); _p->rc = nullptr; }
   else  //e < _p->data：在左侧嫁接（lc或为空，rc == _p必非空）
      { _root = new BinNode<T>( e, nullptr, _p->lc, _p ); _p->lc = nullptr; }
   _p->updateHeightAbove(); _size++; return _root;
} //insert
