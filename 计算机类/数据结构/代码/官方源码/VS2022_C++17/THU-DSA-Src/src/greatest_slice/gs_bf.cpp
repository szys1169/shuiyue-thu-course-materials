/*DSA*/#include <algorithm>
/*DSA*/using namespace std;
/*DSA*/#include "sum/sum.h"
/*DSA*/extern int s_lo, s_hi;
/*DSA*/
int gs_BF( int A[], int n ) { //蛮力策略：O(n^3)
   int gs = 0; //目前已知的最大和 = S[0,0) = 0
   /*DSA*/s_lo = n; s_hi = n;
   for ( int lo = 0; lo < n; lo++ ) //枚举所有的
      for ( int hi = lo+1; hi <= n; hi++ ) { //O(n^2)个区间
         int s = sum(A, lo, hi); //用O(n)时间求和
         /*DSA*/if ( gs <= s ) s_lo = lo;
         /*DSA*/if ( gs < s ) s_hi = hi;
         gs = max( gs, s ); //择优更新
      } //for
   return gs;
} //gs_BF
