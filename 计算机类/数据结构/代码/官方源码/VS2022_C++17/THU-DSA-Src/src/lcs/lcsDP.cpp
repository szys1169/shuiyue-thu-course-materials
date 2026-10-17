/*DSA*/#include <algorithm>
/*DSA*/using namespace std;

uint32_t lcsDP( char const* A, int n, char const* B, int m ) {
   if (n < m) { swap(A, B); swap(n, m); } //确保m<=n，以进一步节省空间
   uint32_t* lcs1 = new uint32_t[m+1]; //只需使用两个数组
   uint32_t* lcs2 = new uint32_t[m+1]; //交替滚动地记录最新的两行
   memset( lcs1, 0x00, sizeof(uint32_t)*(m+1) ); lcs2[0] = 0; //递归基
   for ( int i = 0; i < n; swap(lcs1, lcs2), i++ ) //逐行
      for ( int j = 0; j < m; j++ ) //逐个解出子问题
         lcs2[j + 1] = (A[i] == B[j]) ? 1 + lcs1[j] : max(lcs2[j], lcs1[j+1]);
   uint32_t solu = lcs1[m]; //原问题的解
   delete[] lcs1; delete[] lcs2; return solu;
} //lcsDP
