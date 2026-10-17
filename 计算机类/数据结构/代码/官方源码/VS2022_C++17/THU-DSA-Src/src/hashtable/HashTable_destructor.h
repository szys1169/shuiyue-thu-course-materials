#pragma once

template <typename K, typename V> Hashtable<K, V>::~Hashtable() { //析构前释放桶数组及非空词条
   for ( Rank i = 0; i < M; i++ ) //逐一检查各桶
      if ( ht[i] ) delete ht[i]; //释放非空的桶
   delete ht; //释放桶数组
   delete removed; //释放懒惰删除标记
}
