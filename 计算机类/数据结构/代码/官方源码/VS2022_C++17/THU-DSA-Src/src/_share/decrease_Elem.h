#pragma once

template <typename T> struct Decrease //函数对象：递减一个T类对象
   { void operator() ( T& e ) { e--; } }; //约定T可直接递减或已重载--
