#pragma once
/*DSA*/#include <algorithm>
/*DSA*/using namespace std;

/*DSA*/using Rank = uint32_t; //秩
/*DSA*/template <typename T> struct ListNode;
template <typename T> using LNP = ListNode<T>*; //列表节点位置|List Node Position
template <typename T> struct ListNode { //列表节点模板类（以双向链表形式实现）
   T data; LNP<T> pred, succ; //数值、前驱、后继
   ListNode() {}
   ListNode( const T& e, LNP<T> p = nullptr, LNP<T> s = nullptr )
      : data( e ), pred( p ), succ( s ) {} //类T已定义复制方法
   LNP<T> insertPred( const T& e ); //紧靠当前节点之前插入新节点
   LNP<T> insertSucc( const T& e ); //紧随当前节点之后插入新节点
   void movePred( LNP<T> s ); //转移到紧靠于s之前
   void moveSucc( LNP<T> p ); //转移到紧接于p之后
   LNP<T> operator+( Rank r ); //循秩访问this[r]（效率低）
   Rank operator-( LNP<T> t ); //统计区间[this, t)的长度（效率低）
}; // ListNode
/*DSA*/
/*DSA*/#include "listNode_insert.h"
/*DSA*/#include "listNode_move.h"
/*DSA*/#include "listNode_operator+.h"
/*DSA*/#include "listNode_operator-.h"
