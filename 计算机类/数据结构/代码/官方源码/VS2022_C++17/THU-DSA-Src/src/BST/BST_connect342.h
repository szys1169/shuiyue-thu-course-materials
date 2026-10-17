#pragma once

template <typename T, bool H>
BNP<T> BST<T, H>::connect342( BNP<T> a, BNP<T> T1, BNP<T> b, BNP<T> T2, BNP<T> c ) {
   b->attachLc( a ); a->attachRc( T1 ); a->updateHeight();
   b->attachRc( c ); c->attachLc( T2 ); c->updateHeight();
   return b; //该子树新的根节点，其高度，由调用者负责更新
} //connect342
