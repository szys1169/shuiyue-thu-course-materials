#pragma once

template <typename T> Rank quickSelect( const T* A, Rank n, Rank k ) { //基于快速划分的k选取算法
   Vector<Rank> R(n); for ( Rank i = 0; i < n; i++ ) R.insert(i); //使用索引向量，保持原序列的次序
   for ( Rank lo = 0, hi = n; ; ) { //反复做quickParititon
      swap( R[lo], R[lo + rand()%(hi-lo)] ); T pivot = A[R[lo]]; Rank mi = lo; //大胆猜测
      for ( Rank i = lo+1; i < hi; i++ ) //LGU版partition算法
         if ( A[R[i]] < pivot )
            swap( R[++mi], R[i] );
      swap( R[lo], R[mi] ); //[0,mi) < [mi] <= (mi, n)
      if ( k < mi ) hi = mi; //猜大了，则剪除后缀
      else if ( k == mi ) return R[mi]; //或早或迟，总能猜中
      else lo = mi + 1; //猜小了，则剪除前缀
      //*DSA*/ printf( "%d ~ %d ~ %d : %d\n", lo, k, hi, mi );
      //*DSA*/ for ( Rank i =  0; i < lo; i++ ) printf( "   x" ); printf("\n");
      //*DSA*/ for ( Rank i =  0; i < lo; i++ ) printf( "    " );
      //*DSA*/ for ( Rank i = lo; i < hi; i++ ) printf( "%4d", A[R[i]] ); printf("\n");
      //*DSA*/ for ( Rank i =  0; i < hi; i++ ) printf( "    " ); if (hi < n) printf("%4d", A[R[hi]]);
      //*DSA*/ for ( Rank i = hi+1; i <  n; i++ ) printf( "   x" ); printf( "\n\n\n" );
   } //for
} //quickSelect
