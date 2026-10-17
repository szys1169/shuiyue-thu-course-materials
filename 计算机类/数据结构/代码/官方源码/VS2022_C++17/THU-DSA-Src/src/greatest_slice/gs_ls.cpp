/*DSA*/#include <algorithm>
/*DSA*/using namespace std;
/*DSA*/extern int s_lo, s_hi;
/*DSA*/
int gs_LS( int A[], int n ) { //减治策略：O(n)
   int gs = 0; //目前已知的最大和 = S[n,n) = 0
   /*DSA*/s_lo = n; s_hi = n;
   for ( int sum = 0, k = n-1; 0 <= k; k-- ) { //当前区间[k,n)
      sum += A[k]; //递增地更新后缀和
      /*DSA*/if ( gs < sum ) { s_lo = k; s_hi = n; }
      /*DSA*/if ( sum <= 0 ) { n = k; }
      gs = max( gs, sum ); //择优更新
      sum = max( sum, 0 ); //剪除总和非正的后缀
   } //for
   return gs;
} //gs_LS
