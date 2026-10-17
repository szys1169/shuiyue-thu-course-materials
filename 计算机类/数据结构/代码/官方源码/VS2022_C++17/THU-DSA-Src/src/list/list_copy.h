#pragma once
/*DSA*/#include <algorithm>
/*DSA*/using namespace std;

template <typename T> //依据蓝本列表的区间，复制出当前列表
void List<T>::copy( LNP<T> p, Rank n ) {
   for ( init(); n--; p = p->succ ) //先创建空表；再将蓝本区间内各节点
      insertLast( p->data ); //依次复制，并作为末节点插入
} //时间复杂度线性正比于n，以及每个T类型对象的深复制所需的时间
