#pragma once

template <typename T> //重载下标操作符，以通过秩直接访问列表节点
LNP<T> List<T>::operator[]( Rank r ) const //0 <= r < size
   { return *first() + r; } //O(r)：虽方便，勿多用
