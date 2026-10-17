#include "BST/BST_test.h"

//在子树t中，找到中序遍历次序为r的节点（从0开始编号）
template <typename T> BNP<T> search( BNP<T> t, Rank k ) {
   while (1) { //printf(" --> kth (%d)\t", r);
      Rank ls = t->lc ? t->lc->size() : 0;
      if (ls < k) { t = t->rc; k = k - ls - 1; }
      else if (k < ls) { t = t->lc; }
      else return t;
   }
} //search

//逐层伸展x，直到成为原祖先a的孩子
template <typename T> BNP<T> splayTo( const BNP<T> a, BNP<T> x ) {
   //printf(" --> splay(%d) : ", x->data);
   while ( a != x->parent )
      IsLChild(x) ? x->parent->zig() : x->parent->zag();
   return x;
} //splayTo

//通过zig/zag变换，实现对X的临摹（使当前BST的姿势与X相同）
template <typename T> BNP<T> BinNode<T>::imitate( const BNP<T> y ) {
   BNP<T> s = splayTo( parent, search( this, y->lc ? y->lc->size() : 0 ) );
   if (s->lc) s->lc->imitate(y->lc);
   if (s->rc) s->rc->imitate(y->rc);
   s->updateHeight();
   return s;
} //imitate

template <typename T> void testBST( uint32_t n ) {
   BST<T> Y; while ( Y.size() < n ) Y.insert( dice( n * 3 ) ); print(Y); //随机创建
   BST<T> X; while ( X.size() < n ) X.insert( dice( n * 3 ) ); print(X); //随机创建
   X.imitate( Y ); //临摹
   print( Y ); while ( !Y.empty() ) Y.remove ( Y.root()->data ); //清空
   print( X ); while ( !X.empty() ) X.remove ( X.root()->data ); //清空
} //testBST

int main( int argc, char* argv[] ) {
   if ( 2 > argc ) { printf( "Usage: %s <size of test>\a\a\n", argv[0] ); return 1; }
   srand ( (uint32_t) time( nullptr ) );
   testBST<int>( atoi( argv[1] ) );
   return 0;
} //main
