/******************************************************************************************
 * Test of AVL Tree
 ******************************************************************************************/
#include "AVL_test.h"

/******************************************************************************************
 * Test an AVL
 ******************************************************************************************/
void testAVL( Rank n ) {
   AVL<Rank> avl;
   while ( avl.size() < n ) {
      Rank e = dice( n*3 );
      switch( dice( (Rank) 3 ) ) {
         case 0: { //查找，成功率 <= 33.3%
            printf( "Search(" ); print( e ); printf( ")\t" );
            BNP<Rank> p = avl.search( e );
            p ? print( p ) : printf( "nullptr" );
            break;
         }
         case 1: { //删除，成功率 <= 33.3%
            printf( "Remove(" ); print( e ); printf( ")" );
            avl.remove( e ) ?
               printf( "\n" ), print( avl ) :
               printf( "\tnullptr" );
            break;
         }
         default: {//插入，成功率 == 100%
            printf( "Insert(" ); print( e ); printf( ")\t" );
            BNP<Rank> x = avl.insert( e );
            print( x ), printf( "\n" ), print( avl );
            break;
         }
      } //switch
      printf( "\n" );
   } //while
   while ( avl.size() > 0 ) {
      printf( "Remove(root =" ); print( avl.root()->data ); printf(")\n");
      avl.remove( avl.root()->data );
   } //while
   print( avl );
   while ( avl.size() < 29 ) {
      Rank e = dice( n*3 );
      printf( "Insert(" ); print( e ); printf( ")\t" );
      BNP<Rank> x = avl.insert( e );
      print( x ), printf( "\n" );
   }
   print( avl );
   while ( avl.size() > 0 ) {
      printf( "Remove(root =" ); print( avl.root()->data ); printf(")\n");
      avl.remove( avl.root()->data );
   } //while
   print( avl );
}

/******************************************************************************************
 * 测试主入口
 ******************************************************************************************/
int main( int argc, char* argv[] ) {
   if ( 3 > argc ) { printf( "Usage: %s <size> <tests> \a\a\n", argv[0] ); return 1; }
   srand( ( uint32_t ) time( nullptr ) ); //随机种子
   //srand( 31415926 ); //固定种子（假种子，调试用）
   Rank s = atoi(argv[1]), t = atoi(argv[2]);
   for ( Rank k = 0; k < t; k++ ) {
      printf( "\n[Test #%d/%d]\n", k, t );
      testAVL( s );
   }
   return 0;
}
