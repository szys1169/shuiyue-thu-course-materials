#pragma once

#include "Vector/Vector.h" //以向量为基类，派生出栈模板类
template <typename T> struct Stack: public Vector<T> { //将向量的首/末端作为栈底/顶
   void push( const T& e ) { insert( e ); } //入栈：插入末元素
   T pop() { return remove( _size - 1 ); } //出栈：删除末元素
   T& top() { return _elem[ _size - 1 ]; } //取顶：末元素
}; //Stack
