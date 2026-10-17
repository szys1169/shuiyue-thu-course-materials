#pragma once

template <typename T> void BTree<T>::solveUnderflow( BTNP<T> v ) { //修复下溢
   while ( _m > 2*v->child.size() ) { //v下溢：|key| + 1 == (m-1)/2 == ceil(m/2) - 1 == |child|
      BTNP<T> p = v->parent;
      if ( !p ) { //情况#0：已到树根
         if ( v->key.size() < 1  &&  0 < _size ) //若树根已空（树还没空），则
            { _root = v->child[0]; _root->parent = nullptr; delete v; } //整树降低一层
         break; //随即收工
      } //情况#0
      Rank k = p->child.find( v ); //确认v系p之第k个孩子
      BTNP<T> ls  =  0 < k ? p->child[k-1] : nullptr; //左兄弟
      if ( ls  &&  (_m-1)/2 < ls->key.size() ) { //情况#1L：v有左兄弟，且足够“胖”
         v->key.insert( 0, p->key[ k-1 ] ); //p的轴点关键码转入v（作为最小关键码）
         p->key[ k-1 ] = ls->key.remove(); //ls的最大关键码转入p
         v->child.insert( 0, ls->child.remove() ); //ls的最大孩子过继给v
         if ( v->child[0] ) v->child[0]->parent = v; //作为v的最小孩子
         break; //随即收工
      } //情况#1L
      BTNP<T> rs  =  k < p->key.size() ? p->child[k+1] : nullptr; //右兄弟
      if ( rs  &&  (_m-1)/2 < rs->key.size() ) { //情况1R：v有右兄弟，且足够“胖”
         v->key.insert( p->key[k] ); //p的轴点关键码转入v（作为最大关键码）
         p->key[ k ] = rs->key.remove( 0 ); //rs的最小关键码转入p
         v->child.insert( rs->child.remove( 0 ) ); //rs的最小侧孩子过继给v
         if ( v->child[(_m-1)/2] ) v->child[(_m-1)/2]->parent = v; //作为v的最大孩子
         break; //随即收工
      } //情况#1R
      //情况#2：左、右兄弟均或不存在或不够“胖”，但至少存在其一
      if ( ls ) rs = v; else { ls = v; k++; } //以ls、rs命名之后，以下将rs归入ls
      ls->key.insert( p->key.remove( k-1 ) ); p->child.remove( k ); //p吐还轴点
      rs->child.traverse( SetParent<T>( ls ) ); //rs的孩子们统一指向ls
      ls->child.insert( rs->child ); ls->key.insert( rs->key ); //过继子树及关键码
      delete rs; //右兄弟功成身退
      v = p; //上升一层，继续修复——至多可能上溯O(logn)层、合并O(logn)次
   } //while
} //solveUnderflow
