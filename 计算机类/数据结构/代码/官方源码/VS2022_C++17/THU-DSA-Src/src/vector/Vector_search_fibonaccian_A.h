#pragma once

#include "fibonacci/Fib.h" //引入Fib数列类，预先用O(log_phi(n = hi - lo)时间制作Fib表备查

template <typename T> Rank fibSearch( T* S, const T& e, Rank lo, Rank hi ) {
   /*DSA*///printf( "FIB search(A)\n" );
   for ( Fib fib( hi - lo ); lo < hi; ) { //每步迭代两次比较、三个分支
      while ( hi - lo < fib.get() ) fib.prev(); //自后向前顺序查表（均摊O(1)）
      Rank mi = lo + fib.get() - 1; //确定形如Fib(k)-1的轴点
      if ( e < S[mi] ) hi = mi; //深入前缀[lo, mi)继续查找
      else if ( S[mi] < e ) lo = mi + 1; //深入后缀(mi, hi)继续查找
      else return mi;  //命中，收工：有多个e时，不能保证返回秩最大者
   } //出口时lo==hi
   return -1; //失败，但-1不能指示失败的位置
} //fibSearch
