/*DSA*/#include <algorithm>
/*DSA*/using namespace std;
extern uint32_t** M; //快查表，已用UINT_MAX初始化
uint32_t lcsM( char const* A, int n, char const* B, int m ) {
   if ( n < 1 || m < 1 ) return 0;
   if ( UINT_MAX == M[n-1][m-1] ) //每个子问题，仅递归一次
      M[n-1][m-1] = ( A[n-1] == B[m-1] ) ?
         1 + lcsM( A, n-1, B, m-1 ) :
         max( lcsM( A, n-1, B, m ), lcsM( A, n, B, m-1 ) );
   return M[n-1][m-1];
} //lcsM
