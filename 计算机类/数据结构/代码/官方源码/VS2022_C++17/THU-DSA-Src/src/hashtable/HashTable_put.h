#pragma once

template <typename K, typename V> Entry<K, V>* Hashtable<K, V>::put( K k, V v ) {
   Rank r = probe4Free( k ); //找个空桶（只要装填因子控制得当，必然成功）
   ht[ r ] = new Entry<K, V>( k, v ); removed->clear( r ); //插入新词条，清除懒惰删除标记
   ++N; if ( (N + removed->size())*2 > M ) rehash(); //若装填因子高于50%，重散列
   return ht[ r ]; //词条允许相等；如不允许，调用之前需先get()确认
}
