#pragma once

template <typename T> Rank binSearch( T* S, const T& e, Rank lo, Rank hi ) {
   /*DSA*///printf( "BIN search(A)\n" );
   while ( lo < hi ) { //每步迭代两次比较、三个分支
      Rank mi = (lo + hi) / 2; //以中位数为轴点，区间宽度折半
      if ( e < S[mi] ) hi = mi; //深入前缀[lo,mi)继续查找
      else if ( S[mi] < e ) lo = mi + 1; //深入后缀(mi,hi)继续查找
      else return mi; //命中，收工：有多个e时，不能保证返回秩最大者
   } //出口时lo==hi
   return -1; //失败，但-1不能指示失败的位置
} //版本A
