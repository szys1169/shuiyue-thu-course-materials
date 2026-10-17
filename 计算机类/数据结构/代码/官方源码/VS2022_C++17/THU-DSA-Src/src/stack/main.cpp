/******************************************************************************************
* Test of stack
 ******************************************************************************************/
#include "stack_test.h"

int testID = 0; //测试编号

void testStack( Rank n ) {
   Stack<Rank> S;
   printf( "\n  ==== Test %2d. Growing stack\n", testID++ );
   while ( S.size() < n ) {
      Rank k = dice( (Rank) 100 );
      if ( S.empty() || ( 40 < k ) ) { //60%概率入栈
         Rank e = (Rank) dice( 2*n );
         printf( "push " ); print( e ); printf( " ...\n" );
         S.push( e );
      } else if ( 90 < k ) {
         printf( "top = " ); print( S.top() ); printf( "\n" );
      } else { //30%概率出栈
         printf( "pop = " ); print( S.pop() ); printf( "\n" );
      }
      print( S );
   }
   printf( "\n  ==== Test %2d. Shrinking stack\n", testID++ );
   while ( !S.empty() ) {
      Rank k = dice( (Rank) 100 );
      if ( 70 < k ) { //30%概率入栈
         Rank e = (Rank) dice( 2*n );
         printf( "push " ); print( e ); printf( " ...\n" );
         S.push( e );
      } else if ( k < 10 ) {
         printf( "top = " ); print( S.top() ); printf( "\n" );
      } else { //60%概率出栈
         printf( "pop = " ); print( S.pop() ); printf( "\n" );
      }
      print( S );
   }
}


int main( int argc, char* argv[] ) {
   if ( 2 > argc ) { printf( "Usage: %s <size of test>\a\a\n", argv[0] ); return 1; }
   srand( (uint32_t) time(nullptr) ); //随机种子
   //srand( 31415926 ); //固定种子（假种子，调试用）
   testStack( atoi( argv[1] ) ); //元素类型可以在这里任意选择
   return 0;
}
