#pragma once

template <typename T> struct SetParent {
   BTNP<T> parent; SetParent( BTNP<T> p ) : parent(p) {}
   void operator() ( BTNP<T> x ) { if (x) x->parent = parent; }
}; //SetParent

template <typename T> void BTree<T>::solveOverflow( BTNP<T> v ) { //修复上溢
   while ( _m < v->child.size() ) { //v上溢：|key| == m == |child| - 1
      Rank s = _m/2 + 1; //以中位数为界，将v的后缀分裂出来，创建新节点u
      BTNP<T> u = new BTNode<T>( v->height );
      u->key = Vector<T>( v->key, s ); v->key.remove(s, _m);
      u->child = Vector<BTNP<T>>( v->child, s ); v->child.remove(s, _m+1);
      u->child.traverse( SetParent<T>( u ) ); //u的孩子们统一指向u
      BTNP<T> p = v->parent; //v的父亲p：若为空，则创建之
      if ( !p ) _root = p = new BTNode<T>( 1 + v->height, v ); //全树长高一层
      Rank k = p->child.find( v ); //v在p中的秩
      p->key.insert( k, v->key.remove( s-1 ) ); //轴点上升
      p->child.insert( k+1, u ); u->parent = p; //u与p互联
      v = p; //上升一层，继续修复——至多可能上溯O(logn)层、分裂O(logn)次
   } //while
} //solveOverflow
