#pragma once
#include "binTree/BinNode_macro_BASIC.h"

template <typename T> BNP<T> BinNode<T>::zig() { //顺时针旋转
   BNP<T> v = lc; if ( !v ) return this;
   v->parent = parent;
   if ( parent ) ( IsLChild( this ) ? v->parent->lc : v->parent->rc ) = v;
   lc = v->rc; if ( lc ) lc->parent = this;
   v->rc = this; parent = v;
   updateHeight(); v->updateHeight(); if ( v->parent ) v->parent->updateHeight();
   return v;
} //zig
