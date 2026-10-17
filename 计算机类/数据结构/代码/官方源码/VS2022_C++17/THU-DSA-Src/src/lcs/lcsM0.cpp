/*DSA*/#include <algorithm>
/*DSA*/using namespace std;
uint32_t lcsM(char const* A, int n, char const* B, int m);
uint32_t** M; //二维快查表
uint32_t lcsM0( char const* A, int n, char const* B, int m ) {
   uint32_t* lcs = new uint32_t[n*m]; //一维快查表
   memset( lcs, 0xFF, sizeof( uint32_t )*n*m ); //以UINT_MAX示意“尚未计算”
   M = new uint32_t*[n]; //二维快查表
   for ( int i = 0; i < n; i++ ) M[i] = lcs + m*i;
   uint32_t solu = lcsM( A, n, B, m );
   delete[] lcs;
   return solu;
} //lcsM0
