#include "binTree_test.h"

//随机生成期望高度为h的二叉树
template <typename T> bool randomBinTree( BinTree<T>& A, BNP<T> x, Rank h ) {
   if ( -1 == h ) return false; //至多h层
   if ( 0 < dice( h ) ) //以1/h的概率终止当前分支的生长
      randomBinTree( A, A.insert( x, dice( h*h*h ) ), h - 1 );
   if ( 0 < dice( h ) ) //以1/h的概率终止当前分支的生长
      randomBinTree( A, A.insert( dice( h*h*h ), x ), h - 1 );
   return true;
}

//在二叉树中随机确定一个节点位置
template <typename T> BNP<T> randomPosiInBinTree( BNP<T> root ) {
   if ( IsLeaf( root ) ) return root;
   if ( !root->lc )
      return dice( (Rank) 6 ) ? randomPosiInBinTree( root->rc ) : root;
   if ( !root->rc )
      return dice( (Rank) 6 ) ? randomPosiInBinTree( root->lc ) : root;
   return dice( (Rank) 2 ) ?
      randomPosiInBinTree( root->lc ) :
      randomPosiInBinTree( root->rc ) ;
}

template <typename T> void testBinTree( Rank h ) { //测试二叉树
   int testID = 0; //测试编号

   printf( "\nTest %2d. Generate a binTree of height <= %d\n", testID++, h );
   BinTree<T> A; print( A );
   A.insert( dice( h*h*h ) ); print( A );
   randomBinTree<T>( A, A.root(), h ); print( A );

   printf( "\nTest %2d. Double and increase all nodes by traversal\n", testID++ );
   A.traverse( Double<T>() ); A.traverse( Increase<T>() ); print( A );

   printf( "\nTest %2d. Hailstone all nodes by traversal\n", testID++ );
   Hailstone<T> hs; A.traverse( hs ); print( A );

   printf( "\nTest %2d. Create a MINI HART by attaching\n", testID++ );
   BinTree<T> L(A), R(A);
   BNP<T> x;
   x = L.root(); while (x->lc) x = x->lc; L.attach( A, x ); print(L); //A作为参数被深复制
   x = R.root(); while (x->rc) x = x->rc; R.attach( x, A ); print(R); 
   
   printf( "\nTest %2d. Create a shadow by copying\n", testID++ );
   BinTree<T> B(A); print( B );

   printf( "\nTest %2d. Create a BIG HART by attaching\n", testID++ );
   x = B.root(); while (x->lc) x = x->lc; B.attach( L, x ); //A作为参数被深复制
   x = B.root(); while (x->lc) x = x->lc; B.attach( L, x );
   x = B.root(); while (x->rc) x = x->rc; B.attach( x, R ); //A作为参数被深复制
   x = B.root(); while (x->rc) x = x->rc; B.attach( x, R );
   print( B );

   printf( "\nTest %2d. Remove subtrees\n", testID++ );
   while ( !B.empty() ) {
      BNP<T> p = randomPosiInBinTree( B.root() ); //随机选择一个节点
      if ( dice( (Rank) 2 ) ) {
         printf( "removing " ); print( p->data ); printf( " ...\n" );
         printf( "%d node(s) removed\n", B.remove( p ) ); print( B );
      } else {
         printf( "releasing " ); print( p->data ); printf( " ...\n" );
         BinTree<T> S = B.secede( p ); print( S );
         printf( "%d node(s) released\n", S.size() ); S.remove( S.root() ); print( B );
      }
   }
}

int main( int argc, char* argv[] ) {
   if ( 3 > argc ) { printf( "Usage: %s <depth> <tests>\a\a\n", argv[0] ); return 1; }
   srand( ( uint32_t ) time( nullptr ) );
   //srand( 31415926 ); //固定种子（假种子，调试用）
   Rank s = atoi(argv[1]), t = atoi(argv[2]);
   for ( Rank k = 0; k < t; k++ ) {
      printf( "\n[Round #%d/%d]\n", k, t );
      testBinTree<int>( s );
   }
   return 0;
}
