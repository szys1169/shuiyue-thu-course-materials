#pragma once

template <typename T> struct Cumulate { //函数对象：累计一个T类型对象的数值
   T& s;  Cumulate( T& sum ) : s( sum ) {}
   void operator() ( T& e ) { s += e; } //约定T可直接相加
}; //Cumulate
