#pragma once

/*DSA*/template <typename T> struct Stack;
/*DSA*/template <typename T> struct PQ_ComplHeap;
/*DSA*/template <typename T> class SMMH;
/*DSA*/
/*DSA*/#include <typeinfo>

using Rank = uint32_t; //秩：四字节32位无符号整数
#define DEFAULT_CAPACITY 2 //默认的初始容量（小数值利于充分测试；实际应用中可设置为更大）

template <typename T> class Vector { //向量模板类
   /*DSA*/friend struct Stack<T>; //使之可以直接访问以下的私有成员
   /*DSA*/friend struct PQ_ComplHeap<T>;
   /*DSA*/friend class SMMH<T>;
private:
   T* _elem; Rank _capacity, _size; //数据区、容量、规模
protected:
   void copy( const T* A, Rank lo, Rank hi ); //复制数组区间A[lo, hi)
   void expand( Rank d = 1 ); //若不足以新增d个元素，则扩容
   void shrink(); //若装填因子过小，则缩容
   bool bubble( Rank lo, Rank hi ); //扫描交换
   void bubbleSort( Rank lo, Rank hi ); //起泡排序
   Rank getMax( Rank lo, Rank hi ); //选取最大元素
   void selectionSort( Rank lo, Rank hi ); //选择排序
   void merge( Rank lo, Rank mi, Rank hi ); //二路归并
   void mergeSort( Rank lo, Rank hi ); //归并排序
   void heapSort( Rank lo, Rank hi ); //堆排序
   Rank partition( Rank lo, Rank hi ); //快速划分
   void quickSort( Rank lo, Rank hi ); //快速排序
   void shellSort( Rank lo, Rank hi ); //希尔排序
public:
   Vector( Rank c = DEFAULT_CAPACITY ) //默认构造方法
      { _elem = new T[_capacity = c]; _size = 0; }
   Vector( Rank c, Rank s, T v ) : Vector( c ) //构造并设置各成员，c >= s
      { for ( _size = 0; _size < s; _elem[_size++] = v ); }
   Vector( Vector<T> const& V ) : Vector( V, 0, V._size ) {} //复制向量整体、
   Vector( Vector<T> const& V, Rank lo ) : Vector( V, lo, V._size ) {} //向量后缀、
   Vector( Vector<T> const& V, Rank lo, Rank hi ) : Vector( V._elem, lo, hi ) {} //向量区间、
   Vector( T const* A, Rank lo, Rank hi ): Vector( (hi-lo)*2 ) { copy( A, lo, hi ); } //数组
   ~Vector() { delete [] _elem; } //析构
//静态操作
   Rank size() const { return _size; } //查询规模
   bool empty() const { return !_size; } //判空
   Rank find( const T& e ) const { return find( e, 0, _size ); } //无序向量整体查找
   Rank find( const T& e, Rank lo, Rank hi ) const; //无序向量区间查找
   Rank select( const Rank k ) { return quickSelect( _elem, _size, k ); } //快速选取第k大元素
   Rank search( const T& e ) const { return search( e, 0, _size ); } //有序向量整体查找
   Rank search( const T& e, Rank lo, Rank hi ) const; //有序向量区间查找
//动态操作
   T& operator[]( Rank r ) { return _elem[r]; } //模仿数组元素的引用方式
   const T& operator[]( Rank r ) const { return _elem[r]; } //仅限于右值引用
   Vector<T>& operator= ( Vector<T> const& ); //深复制
   /*DSA*/void traverse( void ( * )( T& ) ); //遍历（函数指针）
   template <typename VST> void traverse( VST& ); //遍历
   T remove( Rank r ); //删除秩为r的元素
   T remove() { return remove( _size - 1 ); } //默认删除末元素
   void remove( Rank lo, Rank hi ); //删除区间[lo,hi)
   void insert( Rank r, const T& e ); //将e插至[r]
   void insert( const T& e ) { return insert( _size, e ); } //默认作为末元素插入
   void insert( Rank r, const T* A, Rank lo, Rank hi ); //将A[lo,hi)插至[r]
   void insert( Rank r, Vector<T>& S, Rank lo, Rank hi ) { insert( r, S._elem, lo, hi ); }
   void insert( Rank r, Vector<T>& S ) { insert( r, S, 0, S._size ); } //将S插至[r]
   void insert( Vector<T>& S ) { insert( _size, S ); } //将S续接至末尾
   void sort( Rank lo, Rank hi ); void sort() { sort( 0, _size ); } //排序
   void unsort( Rank lo, Rank hi ); void unsort() { unsort( 0, _size ); } //置乱
   void dedup(); //无序去重
   void uniquify(); //有序去重
}; //Vector
/*DSA*/
/*DSA*/#include "vector_assignment.h"
/*DSA*/#include "vector_copy.h"
/*DSA*/#include "vector_expand.h"
/*DSA*/#include "vector_shrink.h"
/*DSA*/#include "Vector_insert.h"
/*DSA*/#include "vector_remove.h"
/*DSA*/#include "Vector_find.h"
/*DSA*/#include "../selection/quickselect.h"
/*DSA*/#include "Vector_search.h"
/*DSA*/#include "Vector_search_binary_C.h"
/*DSA*/#include "Vector_search_fibonaccian_B.h"
/*DSA*/#include "Vector_traverse.h"
/*DSA*/#include "Vector_unsort.h"
/*DSA*/#include "Vector_sort.h"
/*DSA*///#include "vector_bubbleSort_A.h"
/*DSA*///#include "vector_bubbleSort_B.h"
/*DSA*/#include "vector_bubbleSort_C.h"
/*DSA*/#include "vector_selectionSort.h"
/*DSA*/#include "vector_merge.h"
/*DSA*/#include "vector_mergeSort.h"
/*DSA*/#include "vector_partition_LUG.h"
/*DSA*///#include "vector_partition_DUP.h"
/*DSA*///#include "vector_partition_LGU.h"
/*DSA*/#include "vector_heapSort.h"
/*DSA*///#include "vector_quickSort_recursive.h"
/*DSA*/#include "vector_quickSort_iterative.h"
/*DSA*/#include "vector_shellSort.h"
/*DSA*/#include "Vector_uniquify.h"
/*DSA*///#include "Vector_uniquify_slow.h"
/*DSA*/#include "Vector_dedup.h"
/*DSA*///#include "Vector_dedup_1.h"
/*DSA*///#include "Vector_dedup_x.h"
