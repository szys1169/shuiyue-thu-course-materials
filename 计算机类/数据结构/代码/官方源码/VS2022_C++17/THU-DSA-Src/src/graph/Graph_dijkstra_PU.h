#pragma once

template <typename Tv, typename Te> struct DijkPU { //针对Dijkstra算法的顶点优先级更新器
   virtual void operator() ( Graph<Tv, Te>* g, Rank v, Rank u ) {
      if ( UNDISCOVERED == g->status( u ) //对于v每一尚未被发现的邻接顶点u，按Dijkstra策略
         && g->priority( u ) > g->priority( v ) + g->weight( v, u ) ) { //策略择优
            g->priority( u ) = g->priority( v ) + g->weight( v, u ); //更新优先级（数）
            g->parent( u ) = v; //更新父亲
      } //if
   } //operator
};
