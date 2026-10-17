#pragma once

template <typename T> struct Half //函数对象：减半一个T类对象
   { void operator()( T& e ) { e /= 2; } }; //约定T可直接减半
