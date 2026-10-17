#pragma once

//沿关键码k的试探链，找到首个可用空桶；实践中有多种试探策略可选，这里仅以线性试探为例
template <typename K, typename V> Rank Hashtable<K, V>::probe4Free( const K& k ) {
   for ( Rank r = hashCode( k ) % M;; r = ( r + 1 ) % M ) //按除余法确定起点，线性试探
      if ( !ht[r] ) //只要有空桶（无论是否带有懒惰删除标志）
         return r; //迟早能找到
} //probe4Free
