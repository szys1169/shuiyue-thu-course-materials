#pragma once

template <typename T> Rank binSearch( T* S, const T& e, Rank lo, Rank hi ) {
   /*DSA*///printf( "BIN search(B)\n" );
   if ( e < S[lo] ) return lo-1; //相当于e = -inf
   while ( 1 < hi - lo ) { //每步迭代一次比较、两个分支；不能提前终止
      Rank mi = (lo + hi) / 2; //以中位数为轴点，区间宽度折半
      if ( e < S[mi] ) hi = mi; //经比较后确定深入前缀[lo,mi)
      else lo = mi; //或后缀[mi,hi)
   } //出口时hi==lo+1，区间仅含一个元素[lo]
   return lo; //无论成功失败，总是返回不超过e的最大者
} //版本B
