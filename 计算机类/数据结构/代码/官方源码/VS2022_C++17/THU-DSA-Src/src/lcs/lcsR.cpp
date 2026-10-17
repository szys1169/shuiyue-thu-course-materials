/*DSA*/#include <algorithm>
/*DSA*/using namespace std;
/*DSA*/
uint32_t lcsR( char const* A, int n, char const* B, int m ) {
   if ( n < 1 || m < 1 ) return 0; //递归基
   if ( A[n-1] == B[m-1] ) //尾字符相同，则减治
      return 1 + lcsR( A, n-1, B, m-1 );
   else //否则，分治
      return max( lcsR( A, n-1, B, m ), lcsR( A, n, B, m-1 ) );
} //每经一次比对，至少有一个序列会缩短一个单位，故知算法必能终止
