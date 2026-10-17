/*DSA*/#include "fac.h"

int main( int argc, char* argv[] ) { //阶乘运算测试
   for ( int i = 0; i < 25; i++ )
      printf( "\t%d\t%22I64d\t%22I64d\n", i, facI( i ), facR( i ) );
   return 0;
} //main
