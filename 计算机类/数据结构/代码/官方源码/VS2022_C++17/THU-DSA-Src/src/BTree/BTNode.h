#pragma once

#include "vector/vector.h"
template <typename T> struct BTNode;
template <typename T> using BTNP = BTNode<T>*; //B-Tree Node Position

template <typename T> struct BTNode {
   BTNP<T> parent; Rank height; //Height(nullptr) == 0
   Vector<T> key; Vector<BTNP<T>> child; //关键码向量、孩子向量（后者长度总是多一个单位）
   BTNode( Rank h = 1, BTNP<T> c = nullptr ) : parent(nullptr), height(h) //即便是空树
      { child.insert(c); if (c) c->parent = this; } //也有一个退化的根节点：无关键码、单分支
}; //BTNode
