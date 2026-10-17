#pragma once

#include <typeinfo>
using Rank = uint32_t;

class Fib { //Fibonacci数列类
private:
   uint64_t f, g; //f = fib(k - 1), g = fib(k)
public:
   Fib( Rank n ) //初始化为不小于n的最小Fibonacci项
   { f = 1; g = 0; while ( g < n ) next(); } //fib(-1), fib(0)，O(log_phi(n))时间
   uint64_t get()  { return g; } //获取当前Fibonacci项，O(1)时间
   uint64_t next() { g += f; f = g - f; return g; } //转至下一Fibonacci项，O(1)时间
   uint64_t prev() { f = g - f; g -= f; return g; } //转至上一Fibonacci项，O(1)时间
};
