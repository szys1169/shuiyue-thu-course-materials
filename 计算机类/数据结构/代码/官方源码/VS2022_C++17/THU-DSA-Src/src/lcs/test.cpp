#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <string>

uint32_t lcsDP(char const* A, int n, char const* B, int m);
uint32_t lcsM0(char const* A, int n, char const* B, int m);
uint32_t lcsR(char const* A, int n, char const* B, int m);

/******************************************************************************************
 * Longest Common Subsequence
 * Example test cases:
 *    HNAJBJDJU   LDVFGDKD
 *    ZEIEZCCTPZ   WPUZALLPBXL
 ******************************************************************************************/
int main( int argc, char* argv[] ) {
   srand( ( uint32_t ) time( nullptr ) ); //随机种子
   //srand( 31415926 ); //固定种子（假种子，调试用） //..\..\_output\LCS\LCS.txt
   int errors = 0, tests = 100;
   for ( int k = 0; k < tests; k++ ) {
      printf("\n%d\n", k);
      char* A; int n; char* B; int m;
      if (2 < argc) {
         m = strlen(argv[2]); B = argv[2];
      } else {
         m = 9 + rand() % 9; B = new char[m + 1];
         for (int j = 0; j < m; j++)
            B[j] = 'A' + (rand() % 26);
         B[m] = 0;
      }
      if (1 < argc) {
         n = strlen(argv[1]); A = argv[1];
      } else {
         n = 9 + rand() % 9; A = new char[n + 1];
         for (int i = 0; i < n; i++)
            A[i] = 'A' + (rand() % 26);
         A[n] = 0;
      }
      uint32_t lcs_i = lcsDP( A, n, B, m );
      uint32_t lcs_m = lcsM0( A, n, B, m );
      uint32_t lcs_r = lcsR( A, n, B, m );
      errors += lcs_i != lcs_m || lcs_m != lcs_r;
      if ( lcs_i == lcs_m )
         printf("%2u == %2u", lcs_i, lcs_m);
      else
         printf("%2u <> %2u", lcs_i, lcs_m);
      if ( lcs_m == lcs_r )
         printf(" == %2u", lcs_r);
      else
         printf(" <> %2u", lcs_r);
      printf(" : %18s [%2d] ~ %18s [%2d]\n", A, n, B, m);
      if ( argc < 3 ) delete[] B;
      if ( argc < 2 ) delete[] A;
   }
   printf("\n%d / %d\n", tests - errors, tests);
   return 0;
}
