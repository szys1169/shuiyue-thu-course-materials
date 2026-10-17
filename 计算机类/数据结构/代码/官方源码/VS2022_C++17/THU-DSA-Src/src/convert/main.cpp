#include "convert.h"

int main() { //进制转换
   srand( (uint32_t) time(nullptr) ); //随机种子
   //srand( 31415926 ); //固定种子（假种子，调试用）
   uint64_t n = 0;
   for ( int i = 0; i < 4; i++ )
      { n <<= 16; n |= (rand() & 0x1) << 15 | rand(); }
   if ( 0 == n ) n = 1;
   for ( int base = 2; base < 17; base++ ) {
      printf( "%20llu_(10) = ", n );
      convert( n, base ); // 进制转换
      printf( "_(%d)\n", base );
   }
   return 0;
}
