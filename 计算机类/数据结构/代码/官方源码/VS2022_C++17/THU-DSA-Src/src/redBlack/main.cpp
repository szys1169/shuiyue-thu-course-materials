/******************************************************************************************
* Test of RedBlack Tree
 ******************************************************************************************/
#include "RedBlack_test.h"

void testRedBlack( Rank n ) {
   RedBlack<Rank> rbt;
   while ( rbt.size() < n ) {
      Rank e = dice( n*3 ); //[0, 3n)范围内的e
      switch( dice( (Rank) 6 ) ) {
         case 0: { //查找（概率 = 1/6）
            printf( "Search(" ); print( e ); printf( ")\n" );
            BNP<Rank> p = rbt.search( e );
            p ?
               printf( "Found With" ), print( p ), printf( "\n" ) :
               printf( "Not Found\n" );
            break;
         }
         case 1:
         case 2: { //删除（概率 = 2/6)
            printf( "Remove(" ); print( e ); printf( ")\n" );
            rbt.remove( e ) ?
               printf( "Done\n" ), print( rbt ) :
               printf( "Not Exists\n" );
            break;
         }
         default: { //插入（概率 = 3/6)
            printf( "Insert(" ); print( e ); printf( ")\n" );
            BNP<Rank> x = rbt.insert( e );
            printf( "Done With" ), print( x ), printf( "\n" ), print( rbt );
            break;
         }
      }
   }
   while ( rbt.size() > 0 ) {
      printf( "Remove(root =" ); print( rbt.root()->data ); printf(")\n");
      rbt.remove( rbt.root()->data );
   }
   print( rbt );
}

int main( int argc, char* argv[] ) {
   if ( 3 > argc ) { printf( "Usage: %s <size> <tests> \a\a\n", argv[0] ); return 1; }
   //srand( (uint32_t) time(nullptr) ); //随机种子
   srand( 31415926 ); //固定种子（假种子，调试用）
   Rank s = atoi(argv[1]), t = atoi(argv[2]);
   for ( Rank k = 0; k < t; k++ ) {
      printf( "\n[Test #%d/%d]\n", k, t );
      testRedBlack( s );
   }
   return 0;
}
