#pragma once

/*DSA*/#include "listNode.h" //引入列表节点类
/*DSA*/
template <typename T> class List { //列表模板类
   /*DSA*/friend class UniPrint;
protected:
   Rank _size; LNP<T> head, tail; //规模、头哨兵、尾哨兵
   void init(); //列表创建时的初始化
   void copy( LNP<T>, Rank ); //复制列表中自位置p起的n项
   void mergeSort( LNP<T>, LNP<T> ); //归并排序
   void selectionSort( LNP<T>, LNP<T> ); //选择排序
   void insertionSort( LNP<T>, LNP<T> ); //插入排序
   void radixSort( LNP<T>, LNP<T> ); //基数排序
public:
   List() { init(); } //默认
   List( List<T> const& L, Rank r, Rank n ) { copy( L[r], n ); } //复制L中自第r项起的n项
   List( List<T> const& L ) { copy( L.first(), L._size ); } //整体复制列表L
   List( LNP<T> p, Rank n ) { copy( p, n ); } //复制列表中自位置p起的n项
   ~List(); //析构
//静态操作
   Rank size() const { return _size; } //规模
   bool empty() const { return _size <= 0; } //判空
   LNP<T> operator[]( Rank r ) const; //重载，支持循秩访问（效率低）
   LNP<T> first() const { return head->succ; } //首节点位置
   LNP<T> last() const { return tail->pred; } //末节点位置
   LNP<T> find( const T& e ) const { return find( head, e, tail ); } //无序查找
   LNP<T> find( LNP<T>, const T&, LNP<T> ) const; //无序区间查找
   LNP<T> search( const T& e ) const { return search( head, e, tail ); } //有序查找
   LNP<T> search( LNP<T>, const T&, LNP<T> ) const; //有序区间查找
   LNP<T> getMax( LNP<T>, LNP<T> ); //找出区间中的最大者
   LNP<T> getMax() { return getMax( head, tail ); } //整体最大者
//动态操作
   /*DSA*/void traverse( void ( * )( T& ) ); //遍历（函数指针）
   template <typename VST> void traverse( VST& ); //遍历（函数对象）
   LNP<T> insertFirst( const T& e ); //将e当作首节点插入
   LNP<T> insertLast( const T& e ); //将e当作末节点插入
   LNP<T> insert( LNP<T> p, const T& e ); //将e当作p的后继插入
   LNP<T> insert( const T& e, LNP<T> p ); //将e当作p的前驱插入
   T remove( LNP<T> ); //删除节点
   void sort( LNP<T>, LNP<T> ); //区间排序
   void sort() { sort( head, tail ); } //整体排序
   /*DSA*/LNP<T> join( List<T>& ); //串接
   void merge( LNP<T>, LNP<T>, LNP<T> ); //区间归并
   void merge( LNP<T> y ) { merge( head, y, tail ); } //整体归并
   void dedup(); //无序去重
   void uniquify(); //有序去重
   /*DSA*/void reverse(); //前后倒置（习题）
}; //List
/*DSA*/
/*DSA*/#include "_share/util.h"
/*DSA*/#include "ListNode.h"
/*DSA*/#include "List_bracket.h"
/*DSA*/#include "List_initialize.h"
/*DSA*/#include "List_copy.h"
/*DSA*/#include "List_destructor.h"
/*DSA*/#include "List_join.h"
/*DSA*/#include "List_find.h"
/*DSA*/#include "List_search.h"
/*DSA*/#include "List_insert.h"
/*DSA*/#include "List_remove.h"
/*DSA*/#include "List_traverse.h"
/*DSA*/#include "List_sort.h"
/*DSA*/#include "List_insertionSort.h"
/*DSA*/#include "List_getMax.h"
/*DSA*/#include "List_selectionSort.h"
/*DSA*/#include "List_merge.h"
/*DSA*/#include "List_mergeSort.h"
/*DSA*/#include "List_radixSort.h"
/*DSA*/#include "List_dedup.h"
/*DSA*/#include "List_uniquify.h"
/*DSA*/#include "List_reverse1.h"
/*DSA*///#include "List_reverse2.h"
/*DSA*///#include "List_reverse3.h"
