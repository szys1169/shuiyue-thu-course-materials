#include "BST_test.h"

Rank testID = 0; //测试编号

template <typename T> void testBST( Rank n ) {
   if ( n < 1 ) return;
   BST<T> bst;

   printf( "\n  ==== Test %2d. stretchToLPath\n", testID++ );
   while ( bst.size() < n ) bst.insert( dice(3*n) ); print( bst ); //随机创建
   bst.stretchToLPath(); print( bst ); //伸直成撇
   while ( !bst.empty() ) bst.remove( bst.root()->data ); print(bst); //清空

   printf( "\n  ==== Test %2d. stretchToRPath\n", testID++ );
   while ( bst.size() < n ) bst.insert( dice( 3 * n ) );
   print( bst ); // 随机创建
   bst.stretchToRPath(); print( bst ); //伸直成捺
   while ( !bst.empty() ) bst.remove( bst.root()->data ); //清空

   printf( "\n  ==== Test %2d. stretchTo[L+R]\n", testID++ );
   while ( bst.size() < n ) bst.insert( dice(3*n) ); print( bst ); //随机创建
   stretchByZig( bst.root()->lc ); //左子树伸直成捺
   stretchByZag( bst.root()->rc ); //右子树伸直成撇
   bst.root()->updateHeight();
   print( bst );
   while ( !bst.empty() ) bst.remove( bst.root()->data ); //清空

   printf( "\n  ==== Test %2d. stretchTo[R+L]\n", testID++ );
   while ( bst.size() < n ) bst.insert( dice(3*n) ); print( bst ); //随机创建
   stretchByZag( bst.root()->lc ); //左子树伸直成撇
   stretchByZig( bst.root()->rc ); //右子树伸直成捺
   bst.root()->updateHeight();
   print( bst );
   while ( !bst.empty() ) bst.remove( bst.root()->data ); //清空

   printf( "\n  ==== Test %2d. Insert + Search + Remove\n", testID++ );
   while ( bst.size() < n ) { // 随机插入、查询、删除
      T e = dice(3*n); //[0, 3n)范围内的e
      switch( dice( (Rank) 3 ) ) {
         case 0: { //查找，成功率 <= 33.3%
            printf( "search(" ); print( e ); printf( "):" );
            BNP<T> p = bst.search( e );
            p ?
               printf( "\tfound with" ), print( p->data ), printf( "\n" ) :
               printf( "\tnot found\n" );
            break;
         }
         case 1: { //删除，成功率 <= 33.3%
            printf( "remove(" ); print( e ); printf( "):" );
            bst.remove( e ) ?
               printf( "\tdone\n" ), print( bst ) :
               printf( "\tnot exists\n" );
            break;
         }
         default: {//插入，成功率 == 100%
            printf( "insert(" ); print( e ); printf( "):" );
            BNP<T> x = bst.insert(e);
            printf( "\tdone with" ), print( x ), printf( "\n" );
            print( bst );
            break;
         }
      }
   }
   while ( bst.size() > 0 ) { //清空
      printf( "removeRoot():" );
      bst.remove( bst.root()->data );
      printf( "\tdone\n" );
      print( bst );
   }
} //testBST

int main( int argc, char* argv[] ) {
   if ( 3 > argc ) { printf( "Usage: %s <size> <tests> \a\a\n", argv[0] ); return 1; }
   //srand( (uint32_t) time(nullptr) ); //随机种子
   srand( 31415926 ); //固定种子（假种子，调试用）
   Rank s = atoi(argv[1]), t = atoi(argv[2]);
   for ( Rank k = 0; k < t; k++ ) {
      printf( "\n[Test #%d/%d]\n", k, t );
      testBST<int>( s );
   }
   return 0;
}
