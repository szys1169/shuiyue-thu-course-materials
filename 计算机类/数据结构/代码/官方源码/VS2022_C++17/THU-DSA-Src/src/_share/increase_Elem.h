#pragma once

template <typename T> struct Increase //函数对象：递增一个T类对象
   { void operator() ( T& e ) { e++; } }; //约定T可直接递增或已重载++
