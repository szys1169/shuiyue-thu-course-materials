#pragma once

template <typename T> BNP<T> Splay<T>::splay( BNP<T> v ) { //节点v伸展至根
   printf("Splay"); print(v); printf("\n");
   while ( BNP<T> p = v->parent ) //自下而上
      if ( BNP<T> g = p->parent ) { //双层伸展
         if ( BNP<T> gg = v->parent = g->parent ) //调整之后
            g == gg->lc ? gg->attachLc( v ) : gg->attachRc( v ); //v应以原曾祖父为父
         switch( ((p == g->rc) << 1) | (v == p->rc) ) { //视p、v之拐向，分四种情况
            case 0b00 : //zig-zig
               g->attachLc( p->rc ); p->attachLc( v->rc );
               p->attachRc( g );     v->attachRc( p );     break;
            case 0b01 : //zig-zag
               p->attachRc( v->lc ); g->attachLc( v->rc );
               v->attachRc( g );     v->attachLc( p );     break;
            case 0b10 : //zag-zig
               p->attachLc( v->rc ); g->attachRc( v->lc );
               v->attachLc( g );     v->attachRc( p );     break;
            default : //0b11 ~ zag-zag
               g->attachRc( p->lc ); p->attachRc( v->lc );
               p->attachLc( g );     v->attachLc( p );     break;
         }
         g->updateHeight(); p->updateHeight();
      } else { //单层伸展：只可能出现在最后一步
         if ( v == p->lc ) { p->attachLc( v->rc ); v->attachRc( p ); }
         else              { p->attachRc( v->lc ); v->attachLc( p ); }
         p->updateHeight(); v->parent = nullptr; break;
      } //else
   (_root = v)->updateHeight(); print(this); return v; //v终成树根
} //splay
