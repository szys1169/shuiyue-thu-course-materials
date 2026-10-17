#include "Hashtable_test.h"

void testHashtable( Rank n ) {
   Hashtable<Rank, char> ht( n ); print( ht );
   while ( ht.size() < 4*n ) {
      switch( dice( (Rank) 3 ) ) {
         case 0: { //查找，成功率 <= 33.3%
            Rank key = dice( n*12 ); //[0, 3n)范围内的key
            printf( "get(" ); print( key ); printf( "~%04d):", hashCode( (int) key ) );
            Entry<Rank, char>* e = ht.get( key );
            if ( e ) { printf( "\tfound with " ); print( e->value ); }
            else printf( "\tnot found" );
            printf( "\n" );
            break;
         }
         case 1: { //删除，成功率 <= 33.3%
            Rank key = dice( n*12 ); //[0, 3n)范围内的key
            printf( "remove(" ); print( key ); printf( "~%04d):", hashCode( (int) key ) );
            if ( ht.remove( key ) ) { printf( "\tdone\n" ); print( ht ); }
            else printf( "\tnot exists\n" );
            break;
         }
         default: {//插入，成功率 == 100%
            Rank key = dice( n*12 ); char value = 'A' + dice( (Rank) 26 ); //在[0, 2n)*['A'~'Z']范围内的词条
            printf( "put(" ); print( key ); printf( "~%04d,", hashCode( (int) key ) ); print( value ); printf( "):" );
            if ( ht.get( key ) ) printf( "\tdup keys\n" ); //不做get()确认，也可顺利put()：如此key相等的多个词条可以并存
            else { ht.put( key, value ); printf( "\tdone\n" ); print( ht ); }
            break;
         }
      } //switch
   } //while
   while ( ht.size() > 0 ) {
      Rank key = dice( n*12 ); //[0, 3n)范围内的key
      printf( "remove(" ); print( key ); printf( "~%04d):", hashCode( (int) key ) );
      if ( ht.remove( key ) ) { printf( "\tdone\n" ); print( ht ); }
      else printf( "\tnot exists\n" );
   } //while
}

int main( int argc, char* argv[] ) {
   if ( 2 > argc ) { printf( "Usage: %s <size of test>\a\a\n", argv[0] ); return 1; }
   //srand( (uint32_t) time(nullptr) ); //随机种子
   srand( 31415926 ); //固定种子（假种子，调试用）
   testHashtable( atoi( argv[1] ) ); //元素类型可以在这里任意选择
   return 0;
}
