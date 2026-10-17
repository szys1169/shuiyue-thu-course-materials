/******************************************************************************************
* Test of queue
 ******************************************************************************************/
#include "queue_sum.h"

int main( int argc, char* argv[] ) {
   if ( 3 > argc ) { printf( "Usage: %s <size> <width>\a\a\n", argv[0] ); return 1; }
   srand( (uint32_t) time(nullptr) ); //随机种子
   //srand( 31415926 ); //固定种子（假种子，调试用）
   Rank n = atoi( argv[1] ), w = atoi( argv[2] ); printf( "n = %d & w = %d\n\n", n, w );
   Queue<int> A;
   for ( Rank i = 0; i < n; i++ )
      A.enqueue( rand() % (2*n) );
   print( A ); qWinSum( A, n, w ); print( A );
   return 0;
}
