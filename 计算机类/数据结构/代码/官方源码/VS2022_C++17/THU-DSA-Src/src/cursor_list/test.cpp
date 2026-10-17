/******************************************************************************************
* Test of Vector
 ******************************************************************************************/
#include "cursor_list.h"

int testCursor( Rank testSize ) { //测试游标式列表
   CursorList<char> CL( testSize ); CL.print(); 
   //CL.insert('A'); CL.insert('B'); CL.insert('C'); CL.insert('D'); CL.insert('E'); CL.print();
   //CL.remove(CL.find('A')); CL.remove(CL.find('B')); CL.remove(CL.find('C')); CL.remove(CL.find('D')); CL.remove(CL.find('E')); CL.print();
   //CL.insert('A'); CL.insert('B'); CL.insert('C'); CL.insert('D'); CL.insert('E'); CL.print();
   for ( Rank i = 0; i < 2*testSize ; i++ ) {
      char x = 'A' + ( rand() % 26 );
      if ( 30 <( rand() % 100 ) ) {
         Rank r = CL.insert( x );
         if ( r < testSize )
            printf( "%c inserted at %d\n", x, r );
         else
            printf( "failed to insert %c into full CL\n", x );
      } else {
         if ( testSize == CL.find( x ) )
            printf( "%c not found\n", x );
         else
            printf( "%c removed at %d\n", x, CL.remove( CL.find( x ) ) );
      }
      CL.print();
   }
   for ( char x = 'A'; x <= 'Z'; x++ ) {
      while ( testSize != CL.find( x ) )
         printf( "%c removed at %d\n", x, CL.remove( CL.find( x ) ) );
      CL.print();
   }
   return 0;
}

int main( int argc, char* argv[] ) {
   if ( 2 > argc ) { printf( "Usage: %s <size of test>\a\a\n", argv[0] ); return 1; }
   srand( (uint32_t) time(nullptr) ); //设置随机种子
   testCursor( atoi( argv[1] ) ); //元素类型可以在这里任意选择
   return 0;
}
