#pragma once

template <typename T> Rank binSearch( T* S, const T& e, Rank lo, Rank hi ) {
   /*DSA*///printf( "BIN search(C)\n" );
   while ( lo < hi ) { //每步迭代一次比较、两个分支；不能提前终止
      Rank mi = (lo + hi) / 2; //以中位数为轴点，区间宽度折半
      if ( e < S[mi] ) hi = mi; //经比较后确定深入前缀[lo,mi)
      else lo = mi + 1; //或后缀(mi,hi)
   } //出口时lo==hi
   return lo - 1; //无论成功失败，总是返回不超过e的最大者
} //版本C
