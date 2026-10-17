#pragma once

#define TallerChild(x) ( /* 在左、右孩子中取更高者 */ \
   Height( (x)->lc ) > Height( (x)->rc ) ? (x)->lc : ( /*左高*/ \
   Height( (x)->lc ) < Height( (x)->rc ) ? (x)->rc : ( /*右高*/ \
      ( (x)->parent && ( (x) == (x)->parent->lc ) ) ? (x)->lc : (x)->rc \
   ) \
   ) \
) //等高时，与x同侧者优先：如此，AVL::remove()算法可将骑墙情况按单旋来简明处理

template <typename T, bool H> BNP<T> BST<T, H>::rotate( BNP<T> g ) { //g->height > 1
   BNP<T> p = TallerChild(g); int TurnP = (p == g->rc);
   BNP<T> v = TallerChild(p); int TurnV = (v == p->rc);
   BNP<T> r = ( TurnP == TurnV ) ? p : v; //子树新的根节点
   ( FromParentTo(g) = r )->parent = g->parent; //须保持与母树的联接
   switch( ( TurnP << 1 ) | TurnV ) { //视p、v的拐向，无非四种情况
         case  0b00   : return connect342( v, v->rc, p, p->rc, g ); //zig-zig
         case  0b01   : return connect342( p, v->lc, v, v->rc, g ); //zig-zag
         case  0b10   : return connect342( g, v->lc, v, v->rc, p ); //zag-zig
      default/*0b11*/ : return connect342( g, p->lc, p, v->lc, v ); //zag-zag
   } //switch
} //rotate
