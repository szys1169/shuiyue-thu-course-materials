#if defined( BITMAP_HOPCROFT )
#include "Bitmap_Hopcroft/Bitmap.h"
#else
#include "Bitmap/Bitmap.h"
#endif

#include "_share/util.h"

int testBitmap( Rank n, int t ) {
   bool* B = new bool[n]; //常规位图
   Bitmap M( n ); //高效位图
   int successes = 0;
   for ( int i = 0; i < t; i++ ) { //重复使用位图多次
      memset( B, 0, n*sizeof( bool ) ); //逐位清零，O(n)
      M.reset(); //逻辑清零，O(1)
      for ( Rank i = 0; i < 3*n; i++ ) { //反复地
         Rank k = dice( n ); //在随机位置上
         if ( dice( (Rank) 2 ) ) { //以50%的概率插入
            B[k] = true; M.set( k );
         } else { //或50%的概率清除
            B[k] = false; M.clear( k );
         }
      }
      //M.set( 29 ); //有时可卖个破绽，以反向测试本测试程序
      int sz = 0; for ( Rank j = 0; j < n; j++ ) sz += B[j];
      printf( "\nM[] x %d %s %d\n", M.size(),( M.size() == sz ? "==" : "<>" ), sz );
      for ( Rank j = 0; j < n; j++ ) printf( "%c", M.test( j ) ? 'x' : '.' );
      if ( M.size() != sz ) { printf( "\nTest %4d ERROR\n", t ); continue; }
      Rank k = 0;
      while ( k++ < n ) //逐位地对比
         if ( B[k] != M.test( k ) ) //一旦发现不合
            break; //随即退出
      if ( k < n ) { //并报告（assert:: k == n+1）
         printf( "\n B[]\n" );
         for ( Rank j = 0; j <= k; j++ ) printf( "%c", B[j] ? 'x' : '.' );
         printf( "\n M[] x %d\n", M.size() );
         for ( Rank j = 0; j <= k; j++ ) printf( "%c", M.test( j ) ? 'x' : '.' );
         printf( "\nTest %4d ERROR\n", i ); 
      } else {
         printf( "\nTest %4d OK\n", i );
         successes++;
      }
   }
   printf( "\nSuccess = %d/%d\n", successes, t);
   delete [] B;
   return 0;
}

int main( int argc, char* argv[] ) {
   if ( 3 > argc ) { printf( "Usage: %s <bitmap size> <#test>\a\a\n", argv[0] ); return 1; }
   srand( (uint32_t) time( nullptr ) ); //随机种子
   //srand( 31415926 ); //固定种子（假种子，调试用）
   return testBitmap( max(0, atoi(argv[1])), max(0, atoi(argv[2]))); //启动测试
}
