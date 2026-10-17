#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <typeinfo>
using Rank = uint32_t;

uint64_t mr_STACK( uint64_t H[], Rank n ); //借助一个栈：O(n)
uint64_t mr_STACKS( uint64_t H[], Rank n ); // 借助两个栈：O(n)
uint64_t mr_BRUTE( uint64_t H[], Rank n ); // 蛮力：O(n^2)

Rank ms = -1, mr = -1, mt = -1; //最大矩形 = H[mr]*(mt-ms)

int main( int argc, char* argv[] ) { //直方图中的最大矩形
   uint64_t* H; Rank n; //宽度为n的直方图
   if ( 1 < argc ) { //命令行指定，比如：77 4 120 16 96 59 0 15 123 8 79 73 57 96 84 101 26 12 88 81 111 18 87 117 46 90 94 70 125
      H = new uint64_t[ n = argc -1 ];
      for ( Rank i = 0; i < n; i++ )
         H[i] = atoi( argv[i+1] );
   } else { //随机生成
      srand( (uint32_t) time(nullptr) );
      H = new uint64_t[ 1 + ( n = rand() % 128 ) ];
      for ( Rank i = 0; i < n; i++ )
         H[i] = rand() % 128;
   }

   uint64_t mrBrute = mr_BRUTE( H, n );
   printf( "MaxRect Brute-Force  : %I64d = %I64d x [%d,%d)\n", mrBrute, H[mr], ms, mt );
   uint64_t mrStacks = mr_STACKS( H, n );
   printf( "MaxRect using STACKS : %I64d = %I64d x [%d,%d)\n", mrStacks, H[mr], ms, mt );
   uint64_t mrStack  = mr_STACK( H, n );
   printf( "MaxRect using STACK  : %I64d = %I64d x [%d,%d)\n", mrStack, H[mr], ms, mt );

   for ( Rank i = 0; i < ms; i++ ) {
      printf("%20I64d [%3d]: ", H[i], i);
      for ( int j = 0; j < H[i]; j++ ) printf("."); printf("\n");
   }
   for ( Rank i = ms; i < mr; i++ ) {
      printf("%20I64d [%3d]: ", H[i], i);
      for ( int j = 0; j < H[i]; j++ ) printf( (j < H[mr]) ? "#" : "." ); printf("\n");
   }
   {
      printf("%20I64d [%3d]: ", H[mr], mr);
      for ( int j = 0; j < H[mr]; j++ ) printf("O"); printf("\n");
   }
   for ( Rank i = mr+1; i < mt; i++ ) {
      printf("%20I64d [%3d]: ", H[i], i);
      for ( int j = 0; j < H[i]; j++ ) printf( (j < H[mr]) ? "#" : "." ); printf("\n");
   }
   for ( Rank i = mt; i < n; i++ ) {
      printf("%20I64d [%3d]: ", H[i], i);
      for ( int j = 0; j < H[i]; j++ ) printf("."); printf("\n");
   }

   delete [] H;
   return 0;
} //main
