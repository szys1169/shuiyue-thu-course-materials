#pragma once

// 重散列：散列函数的定址与表长M直接相关，不可简单地批量复制原桶数组
template <typename K, typename V> void Hashtable<K, V>::rehash() {
   Rank M0 = M; M = primeNLT( 4*N, 1048576, PRIME_TABLE ); //新的容量
   Entry<K, V>** ht0 = ht; ht = new Entry<K, V>*[M]; //懒惰删除标记很多时，可能反而缩容
   memset( ht, 0, sizeof( Entry<K, V>* )*M ); //初始清空
   for ( Rank i = 0; i < M0; i++ ) //遍历原表
      if ( ht0[i] ) //每个词条
         ht[ probe4Free( ht0[i]->key ) ] = ht0[i]; //直接移入新表
   /*DSA*/printf("\nrehash(%d -> %d)\n", M0, M);
   delete removed; removed = new Bitmap( M ); //懒惰删除标记
   delete[] ht0; //原表至此已空，释放之
} //rehash
