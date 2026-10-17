#pragma once

template <typename T, bool H> BNP<T> BST<T, H>::search( const T& e ) { //在BST中查找关键码e
   for ( _p = nullptr, _x = _root; _x && ( e != _x->data );  ) { //自顶而下
      _p = _x; //_p紧随_x，亦步亦趋
      _x = ( e < _x->data ? _x->lc : _x->rc ); //向左或右，x逐层深入
   } //直至_x命中，或抵达nullptr
   return _x; //无论命中与否，_x为终点，_p为其父
} //特别地，命中于树根时，_x == _root且_p == nullptr；树空时，_p == _x == nullptr
