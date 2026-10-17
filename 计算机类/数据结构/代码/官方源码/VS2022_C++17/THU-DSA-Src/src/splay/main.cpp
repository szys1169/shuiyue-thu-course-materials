#include "Splay_test.h"

void testSplay( Rank n ) {
   Splay<Rank> splay;

//随机访问
   while ( splay.size() < n ) {
      Rank e = dice( n*3 );
      switch( dice( (Rank) 3 ) ) {
         case 0: { //查找，成功率 <= 33.3%
            printf( "Search" ); print( e ); printf("\n");
            splay.search( e );
            break;
         }
         case 1: { //删除，成功率 <= 33.3%
            printf( "Remove" ); print( e ); printf("\n");
            if ( splay.remove( e ) ) print( splay );
            break;
         }
         default: {//插入，成功率 == 100%
            printf( "Insert" ); print( e ); printf("\n");
            splay.insert( e ); print( splay );
            break;
         }
      } //switch
   } //while
   while ( splay.size() > 0 ) {
      Rank e = dice( n*3 );
      printf( "Remove" ); print( e );
      splay.remove( e );
   } //while

//单调访问
   for ( Rank i = 0; i < n; i++ ) splay.insert( i ); print( splay );
   for ( Rank i = 0; i < n; i++ ) { splay.search( i ); print( splay ); }
} //课后：利用这一接口，针对不同分布的访问，验证课上关于Splay均摊性能的结论

int main( int argc, char* argv[] ) { //测试主入口
   if ( 3 > argc ) { printf( "Usage: %s <size> <tests>\a\a\n", argv[0] ); return 1; }
   //srand( (uint32_t) time(nullptr) ); //随机种子
   srand( 31415926 ); //固定种子（假种子，调试用）
   Rank s = atoi(argv[1]), t = atoi(argv[2]);
   for ( Rank k = 0; k < t; k++ ) {
      printf( "\n[Test #%d/%d]\n", k, t );
      testSplay( s );
   }
   return 0;
}
