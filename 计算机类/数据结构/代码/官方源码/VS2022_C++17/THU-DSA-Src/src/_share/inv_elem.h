#pragma once

template <typename T> struct Compare { //判断线性序列中的一个元素是否与其前驱顺序
   T pred; int& i;  Compare( int& invs, T& first ) : pred( first ), i( invs ) {}
   void operator() ( T& e ) { i += ( pred > e ); pred = e; } //约定T可比较
}; //Compare
