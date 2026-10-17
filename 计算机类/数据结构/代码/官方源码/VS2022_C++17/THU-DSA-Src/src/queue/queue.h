#pragma once

#include "List/List.h" //以List为基类，派生出队列模板类
template <typename T> struct Queue: public List<T> { //将列表的首/末端作为队首/尾
   void enqueue( const T& e ) { insertLast( e ); } //入队：尾部插入
   T dequeue() { return remove( first() ); } //出队：首部删除
   T& front() { return first()->data; } //队首：首节点
}; //List
