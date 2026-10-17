/******************************************************************************************
* Test of Skiplist
 ******************************************************************************************/

#include "skipList_test.h"

void testSkiplist( Rank n, Rank times ) {
   Skiplist<Rank> L; print( L );
   for ( Rank ttt = 0; ttt < times; ttt++ ) { //n规模的测试做times遍
      printf( "\n[Test #%d/%d]\n", ttt, times );
      while ( L.size() < n ) {
         Rank e = dice( n*3 ); //[0, 3n)范围内的e
         switch( dice( (Rank) 3 ) ) {
            case 0: { //查找
               printf( "search(" ); print( e ); printf( "):" );
               TowerPosi<Rank> t = L.search( e );
               printf( "\tfound with" );
               t ? print( key(t) ) : printf( " -inf" );
               printf("\n");
               break;
            }
            case 1: { //删除
               printf( "remove(" ); print( e ); printf( "):" );
               if ( L.remove( e ) ) { printf( "\tdone\n" ); print(L); }
               else printf( "\tnot exists\n" );
               break;
            }
            default: {//插入
               printf( "insert(" ); print( e ); printf( "):" );
               Rank sizeOld = L.size(); L.insert( e );
               printf( ( sizeOld != L.size() ) ? "\tdone\n" : "\tdup\n" );
               print( L );
               break;
            }
         } //switch
      } //while

      while ( L.size() > 0 ) {
         Rank e = dice( n*3 ); //[0, 3n)范围内的e
         printf( "search(" ); print( e ); printf( "):" );
         TowerPosi<Rank> t = L.search( e );
         printf( "\tfound with" );
         t ? print(key(t)) : printf(" -inf");
         printf("\n");

         e = t ? key(t) : e = key(L.first()); //删除最接近的目标
         printf( "remove(" ); print( e ); printf( "):" );
         if ( L.remove( e ) ) { printf( "\tdone\n" ); print( L ); }
         else printf( "\tnot exists\n" ); //-inf
      } //while
   } //while
}

int main( int argc, char* argv[] ) {
   if ( 3 > argc ) { printf( "Usage: %s <size> <tests> \a\a\n", argv[0] ); return 1; }
   //srand( (uint32_t) time(nullptr) ); //随机种子
   srand( 31415926 ); //固定种子（假种子，调试用）
   testSkiplist( atoi(argv[1]), atoi(argv[2]) );
   return 0;
}
