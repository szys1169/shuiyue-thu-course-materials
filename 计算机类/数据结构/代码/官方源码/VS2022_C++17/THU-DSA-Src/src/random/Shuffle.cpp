/*DSA*/#include <iostream>
/*DSA*/using namespace std;

void shuffle( int A[], int n ) { //将A[0, n)随机打乱
   for ( ; 1 < n; --n ) //自后向前
      swap( A[rand() % n], A[n - 1] );
}

void shuffle( int A[], int lo, int hi ) //将A[lo, hi)随机打乱
   { shuffle( A + lo, hi - lo ); }
