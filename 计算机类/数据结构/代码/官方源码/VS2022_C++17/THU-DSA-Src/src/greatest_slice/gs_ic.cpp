/*DSA*/#include <algorithm>
/*DSA*/using namespace std;
/*DSA*/extern int s_lo, s_hi;
/*DSA*/
int gs_IC( int A[], int n ) { //递增策略：O(n^2)
   int gs = 0; //目前已知的最大和 = S[0,0) = 0
   /*DSA*/s_lo = n; s_hi = n;
   for ( int lo = 0; lo < n; lo++ ) //枚举所有起始于lo
      for ( int s = 0, hi = lo; hi < n; ) { //终止于hi的区间
         s += A[hi++]; //递增地得到其总和：O(1)
         /*DSA*/if ( gs <= s ) s_lo = lo;
         /*DSA*/if ( gs < s ) s_hi = hi;
         gs = max( gs, s ); //择优更新
      } //for
   return gs;
} //gs_IC
