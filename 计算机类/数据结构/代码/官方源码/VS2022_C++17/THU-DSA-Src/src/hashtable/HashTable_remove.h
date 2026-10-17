#pragma once

template <typename K, typename V> bool Hashtable<K, V>::remove( K k ) { //散列表词条删除算法
   Rank r = probe4Hit( k ); if ( !ht[r] ) return false; //确认目标词条存在
   delete ht[r]; ht[r] = nullptr; --N; removed->set(r); return true; //清除词条，设置懒惰删除标记
}
