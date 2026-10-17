#pragma once

template <typename T> //对各自有序的[lo,mi)和[mi,hi)做归并
void Vector<T>::merge( Rank lo, Rank mi, Rank hi ) { //lo < mi < hi
   Rank s = 0; T* S = _elem + lo; //就地归并至序列S[0,hi-lo)
   Rank a = 0, la = mi - lo; T* A = new T[la]; //A[0,la)复制自
   for ( Rank i = 0; i < la; i++ ) A[i] = S[i]; //S的前缀
   Rank b = 0, lb = hi - mi; T* B = S + la; //B[0,lb)就是S的后缀
   while ( ( a < la ) && ( b < lb ) ) //反复地比较A、B的首元素
      S[s++] = ( A[a] <= B[b] ) ? A[a++] : B[b++]; //小者优先归入S
   while ( a < la ) //若B先耗尽，则还需将A残余的后缀归入S
      S[s++] = A[a++]; //反之若A先耗尽，因B残余的后缀已在S中，故无需处理
   delete[] A; //new和delete很耗时，如何减少？
} //merge
