/*DSA*/#include <algorithm>
/*DSA*/using namespace std;
/*DSA*/extern int s_lo, s_hi;
/*DSA*/
int gs_DC( int A[], int lo, int hi ) { //分治策略：O(n*logn)
   if ( hi - lo < 2 ) return A[lo];
   int mi = (lo + hi) / 2; int gsL = 0, gsR = 0; //前缀|后缀中的最大后缀|前缀
   for ( int s = 0, i = mi-1; lo <= i; i-- ) //枚举[lo,mi)的所有后缀
      gsL = max(gsL, s += A[i]); //择优更新
   for ( int s = 0, j = mi; j < hi; j++ ) //枚举[mi,hi)的所有前缀
      gsR = max(gsR, s += A[j]); //择优更新
   return max( gsL + gsR, max( gs_DC( A, lo, mi ), gs_DC( A, mi, hi ) ) ); //递归
} //gs_DC
