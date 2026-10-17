#include <cstdio>
#include "_share/rand.h"
#include "Bitmap/Bitmap.h"
#include "Eratosthenes.h"
#include "primeNLT.h"

#define PRIMEFILE "prime-bitmap.txt" //用于记录指定区间内素数分布的比特图文件

int main( int argc, char* argv[] ) {
   if ( 2 > argc ) { printf( "Usage: %s <maxInt>\n", argv[0] ); return -1; }
   srand( (uint32_t) time(nullptr) ); //随机种子
   //srand( 31415926 ); //固定种子（假种子，调试用）
   Rank n = atoi( argv[1] ); //简化起见，不考虑非正的情况
   eratosthenes( n, PRIMEFILE );
   for ( Rank i = 0; i <= 13; i++ ) { //做13次随机测试（限于MAX_RAND，覆盖范围不超过0x7FFF）
      Rank low = dice( n );
      printf( "The smallest prime number no less than %8d(%05X) is %8d\n", low, low,
              primeNLT( low, n, PRIMEFILE ) );
   }
   for ( Rank i = 0; i < 13; i++ ) { //做13次等间距测试
      printf( "The smallest prime number no less than %8d(%05X) is %8d\n", n*i/11,
              n* i / 11, primeNLT( n*i/11, n, PRIMEFILE ) );
   }
   return 0;
}
