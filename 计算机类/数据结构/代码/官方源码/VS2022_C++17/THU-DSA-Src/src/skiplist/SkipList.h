#pragma once

/*DSA*/#include "Vector/Vector.h"
/*DSA*/#include "List/List.h"

template <typename T> struct Tower;
template <typename T> using TowerPosi = LNP<Tower<T>>;
template <typename T> struct Brick { //塔的一层
   TowerPosi<T> pred, succ;
   Brick( TowerPosi<T> p = nullptr, TowerPosi<T> s = nullptr )
      : pred(p), succ(s) {}
};
#define key(t) ((t)->data.data)
#define tower(t) ((t)->data.tower)
#define height(t) (tower(t).size())
/*DSA*///template <typename T> constexpr inline T key( TowerPosi<T> t ) { return t->data.data; }
/*DSA*///template <typename T> constexpr inline Vector<Brick<T>>& tower( TowerPosi<T> t ) { return t->data.tower; }
/*DSA*///template <typename T> constexpr inline Rank height( TowerPosi<T> t ) { return tower(t).size(); }
template <typename T> struct Tower {
   T data; Vector<Brick<T>> tower; //关键码、塔
   Tower( T e = (T) 0  ): data(e) {} //初始均为空塔
};
template <typename T> struct Skiplist : public List<Tower<T>> {
   TowerPosi<T> _x; //最近一次操作所在的塔
   TowerPosi<T> search( const T& ); //查找
   TowerPosi<T> insert( const T& ); //插入
   bool remove( const T& ); //删除
}; //Skiplist
/*DSA*/
/*DSA*/#include "Skiplist_search.h"
/*DSA*/#include "Skiplist_insert.h"
/*DSA*/#include "Skiplist_remove.h"
