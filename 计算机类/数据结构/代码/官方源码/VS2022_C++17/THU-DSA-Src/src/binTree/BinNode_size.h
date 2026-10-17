#pragma once

template <typename T> Rank BinNode<T>::size() { //统计子树规模，亦即当前节点的后代总数
   Rank s = 1; //先计入本身
   if ( lc ) s += lc->size(); //递归计入左子树规模
   if ( rc ) s += rc->size(); //递归计入右子树规模
   return s; //也可改由中序、后序遍历得到
} //O(n=size)：懒惰策略，现用现算；也可改为勤奋策略，始终动态维护
