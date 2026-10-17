/******************************************************************************************
* Test of B-Tree
******************************************************************************************/
#include "BTree_test.h"

/******************************************************************************************
* Test a BTree
******************************************************************************************/
void testBTree( Rank m, Rank n ) {
   BTree<Rank> bt( m );
   while ( bt._size < n ) { // 随机
      Rank e = dice( n*3 );
      switch( dice( (Rank) 3 ) ) {
         case 0: { //查找，成功率 <= 33.3%
            printf( "Search(" ); print( e ); printf( ")\t" );
            BTNP<Rank> x = bt.search( e ); Rank k = x->key.search( e );
            printf( e == x->key[k] ? "Found\n" : "Not Found\n" );
            break;
         }
         case 1: { //删除，成功率 <= 33.3%
            printf( "Remove(" ); print( e ); printf( ")\t" );
            if ( bt.remove( e ) ) {
               printf( "Done\n" ); print( bt );
            } else
               printf( "Not Found\n" );
            break;
         }
         default: {//插入，成功率 == 100%
            printf( "Insert(" ); print( e ); printf( ")\t" );
            if ( bt.insert( e ) ) {
               printf( "Done\n" ); print( bt );
            } else
               printf( "Dup\n" );
            break;
         }
      }
   }
   while ( bt._size > 0 ) { //清空
      Rank e = rand() % (n*3); //dice(n*3);
      if ( bt.remove( e ) )
         { printf( "Remove(" ); print( e ); printf( ")\tDone\n" ); print( bt ); }
   }
   for ( Rank e = 0; e < n; e++ ) //顺序插入
      bt.insert( e*3 );
   print( bt );
   while ( bt._size > 0 ) { //清空
      Rank e = (rand() % n) * 3; //dice(n)*3;
      if ( bt.remove( e ) )
         { printf( "Remove(" ); print( e ); printf( ")\tDone\n" ); print( bt ); }
   }
}

/******************************************************************************************
* 测试主入口
******************************************************************************************/
int main( int argc, char* argv[] ) {
   if ( 4 > argc ) { printf( "Usage: %s <order> <size> <tests>\a\a\n", argv[0] ); return 1; }
   Rank m = atoi( argv[1] ); if ( m < 3 )  { printf( "Make sure the order(%d) is no less than 3.\a\a\n", m ); return 1; }
   Rank s = atoi( argv[2] );
   //srand( (uint32_t) time(nullptr) );
   srand( 31415926 ); //固定种子
   Rank t = atoi(argv[3]);
   for ( Rank k = 0; k < t; k++ ) {
      testBTree( m, s );
      printf( "[Test #%d/%d] Done\n\n", k, t );
   }
   return 0;
}
