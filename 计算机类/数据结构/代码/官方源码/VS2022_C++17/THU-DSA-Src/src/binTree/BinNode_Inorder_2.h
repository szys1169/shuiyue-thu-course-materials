#pragma once
#include <iostream>

auto first = [](auto x) { return eov(x); }; //中序的首节点即EOV；其它遍历需相应重写
template <typename T, typename V> void inorder2( BNP<T> x, V& visit ) {
   for ( x = first(x); x; x = x->succ() ) //依次
      visit( x->data ); //枚举所有节点
} //inorder2
