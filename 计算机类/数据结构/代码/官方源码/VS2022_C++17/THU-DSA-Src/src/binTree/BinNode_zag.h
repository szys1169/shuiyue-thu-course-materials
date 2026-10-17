#pragma once
#include "binTree/BinNode_macro_BASIC.h"

template <typename T> BNP<T> BinNode<T>::zag() { //逆时针旋转
   BNP<T> v = rc; if ( !v ) return this;
   v->parent = parent;
   if ( parent ) ( IsLChild( this ) ? v->parent->lc : v->parent->rc ) = v;
   rc = v->lc; if ( rc ) rc->parent = this;
   v->lc = this; parent = v;
   updateHeight(); v->updateHeight(); if ( v->parent ) v->parent->updateHeight();
   return v;
} //zag
