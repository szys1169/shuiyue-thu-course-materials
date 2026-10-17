#pragma once

template <typename T> T Vector<T>::remove( Rank r ) { //删除向量中秩为r的元素，0 <= r < size
   T e = _elem[r]; //备份被删除元素
   remove( r, r+1 ); //调用区间删除算法，等效于对区间[r,r+1)的删除
   return e; //返回被删除元素
}

template <typename T> void Vector<T>::remove( Rank lo, Rank hi ) { //0 <= lo <= hi <= n
   while ( hi < _size ) _elem[lo++] = _elem[hi++]; //后缀：自前向后地前移，O(n - hi)
   _size = lo; shrink(); //更新规模，可能缩容
} //O(n-hi)：正比于后缀长度，而与hi-lo无关
