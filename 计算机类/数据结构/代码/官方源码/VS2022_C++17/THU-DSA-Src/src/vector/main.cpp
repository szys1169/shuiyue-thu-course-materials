/******************************************************************************************
* Test of Vector
 ******************************************************************************************/
#include "vector_test.h"

int testID = 0; //测试编号

void TestFind( Vector<Rank>& V ) { //测试：无序向量的（顺序）查找
   for ( Rank i = 0; i < V.size(); i++ ) { //依次查找向量中元素，当然成功
      Rank e =  V[i]; printf("Find("); print( e ); printf("):\t");
      Rank r = V.find( e );
      if ( -1 != r ) printf( "V[%4d] = %4d\n", r, V[r] );
      else printf( "V[%4d] <> %4d\a\a\n", r, e );
   }
   for ( Rank i = 0; i <= V.size(); i++ ) { //依次查找每对相邻元素的均值，可能成功
      Rank a = ( 0 < i ) ? V[i - 1] : V[0] - 4;
      Rank b = ( i < V.size() ) ? V[i] : V[V.size()-1] + 4;
      Rank e = ( a + b ) / 2; printf("Find("); print( e ); printf("):\t");
      Rank r = V.find( e );
      if ( -1 != r ) printf( "V[%4d] = %4d\n", r, V[r] );
      else printf( "V[%4d]<> %4d\n", r, e );
   }
}

void TestSearch( Vector<Rank>& V ) { //测试：有序向量的查找（binSearch或fibSearch）
   for ( Rank i = 0; i < V.size(); i++ ) { //依次查找向量中元素，当然成功
      Rank e =  V[i]; printf("Search("); print( e ); printf("):\t");
      Rank r = V.search( e );
      if ( V[r] == e ) printf( "V[%4d] = %4d\n", r, V[r] );
      else printf( "V[%4d] = %4d<> %4d\a\a\n", r, V[r], e );
   }
   for ( Rank i = 0; i <= V.size(); i++ ) { //依次查找相邻元素的均值，可能成功
      Rank a = ( 0 < i ) ? V[i - 1] : V[0] - 4;
      Rank b = ( i < V.size() ) ? V[i] : V[V.size()-1] + 4;
      Rank e = ( a + b ) / 2; printf("Search("); print( e ); printf("):\t");
      Rank r = V.search( e );
      printf( "V[%4d] =", r ); ( -1 == r ) ? print( "-INF" ) : print( V[r] ); printf( "  ~  " );
      printf( "V[%4d] =", r + 1 ); ( r + 1 < V.size() ) ? print( V[r + 1] ) : print( "+INF" );
      printf("\n");
   }
}

void TestOrderedInsertion( Vector<Rank>& V, Rank n ) {
   while ( n*2 > V.size() ) {
      Rank e = dice( ( Rank ) n*2 ); printf("Insert("); V.insert( V.search( e ) + 1, e );
      print( e ); printf( ")\n" ); PRINT( V );
   }
}

void testVector( Rank testSize ) {
   printf( "\n==== Test %2d. Generate a random vector\n", testID++ );
   Vector<Rank> V;
   for ( Rank i = 0; i < testSize; i++ ) //在[0,3n)中随机选择n个数
      V.insert( dice( i + 1 ), dice( testSize*3 ) );
   PRINT( V );
//
   printf( "\n==== Test %2d. Sort by selection\n", testID++ );
   Vector<Rank> S(testSize);
   for ( Rank k = 0; k < testSize; k++ )
      S.insert( V[V.select( k )] ); //将第k大的元素放到[k]
   PRINT( S );
//
   printf( "\n==== Test %2d. Insert Interval\n", testID++ );
   Rank gap = testSize/59;
   for ( Rank k = testSize;  gap < k+gap; k -= gap )
      S.insert( max<Rank>( k, gap ) -  gap, V, max<Rank>( k, gap ) - gap, k );
   PRINT( S );
//
   printf( "\n==== Test %2d. unsort\n", testID++ );
   V.unsort(); PRINT( V );
//
   printf( "\n==== Test %2d. Lowpass on\n", testID++ ); PRINT( V );
   int i = V.size(); while ( 0 < --i ) { V[i-1] *= 7; V[i-1] += V[i]; V[i-1] >>= 3; }    PRINT( V );
//
   printf( "\n==== Test %2d. Increase\n", testID++ ); PRINT( V );
   increase( V ); PRINT( V );
//
   printf( "\n==== Test %2d. FIND in\n", testID++ ); PRINT( V );
   TestFind( V );
//
   printf( "\n==== Test %2d. Sort degenerate intervals each of size 1 in\n", testID++ ); PRINT( V );
   for ( Rank i = 0; i < V.size(); i += V.size() / 5 ) { V.sort( i, i+1 ); PRINT( V ); } //element by element
   Rank trunk = (V.size()+4)/5;
//
   printf( "\n==== Test %2d. Sort %d intervals each of size <=%d in\n", testID++, V.size()/trunk, trunk ); PRINT( V );
   for ( Rank i = 0; i < V.size(); i += trunk ) { printf("[%d , %d)\n", i, min( V.size(), i + trunk ) ); V.sort( i, min( V.size(), i + trunk ) ); PRINT( V ); } //interval by interval
//
   printf( "\n==== Test %2d. Sort the entire vector\n", testID++ ); PRINT( V );
   V.sort(); PRINT( V );
//
   printf( "\n==== Test %2d. FIND in\n", testID++ ); PRINT( V );
   TestFind( V );
//
   printf( "\n==== Test %2d. SEARCH in\n", testID++ ); PRINT( V );
   TestSearch( V );
//
   printf( "\n==== Test %2d. Unsort interval [%d, %d) in\n", testID++, V.size() / 4, 3*V.size() / 4 ); PRINT( V );
   V.unsort( V.size()/4, 3*V.size() / 4 ); PRINT( V );
//
   printf( "\n==== Test %2d. Unsort interval [%d, %d) in\n", testID++, 0, V.size() ); PRINT( V );
   V.unsort(); PRINT( V );
//
   printf( "\n==== Test %2d. Copy interval [%d, %d) from\n", testID++, V.size() / 4, 3*V.size() / 4 ); PRINT( V );
   Vector<Rank> U( V, V.size()/4, 3*V.size() / 4 ); PRINT( U );
//
   printf( "\n==== Test %2d. Copy from\n", testID++ ); PRINT( V );
   Vector<Rank> W( V ); PRINT( W );
//
   printf( "\n==== Test %2d. Clone from\n", testID++ ); PRINT( U );
   W = U; PRINT( W );
//
   printf( "\n==== Test %2d. Remove redundancy in unsorted\n", testID++ ); PRINT( V );
   Rank oldSize = V.size(); V.dedup();
   printf( "%d element(s) removed\n", oldSize - V.size() ); PRINT( V );
//
   printf( "\n==== Test %2d. Sort the entire vector\n", testID++ ); PRINT( V );
   V.sort(); PRINT( V );
//
   printf( "\n==== Test %2d. Remove redundancy in sorted\n", testID++ ); PRINT( V );
   oldSize = V.size(); V.uniquify();
   printf( "%d element(s) removed\n", oldSize - V.size() ); PRINT( V );
//
   printf( "\n==== Test %2d. FIND in\n", testID++ ); PRINT( V );
   TestFind( V );
//
   printf( "\n==== Test %2d. SEARCH & INSERT in\n", testID++ ); PRINT( V );
   TestOrderedInsertion( V, testSize );  PRINT( V );
//
   printf( "\n==== Test %2d. Remove redundancy in sorted\n", testID++ ); PRINT( V );
   oldSize = V.size(); V.uniquify();
   printf( "%d element(s) removed\n", oldSize - V.size() ); PRINT( V );
}

int main( int argc, char* argv[] ) {
   if ( 3 > argc ) { printf( "Usage: %s <size> <tests> \a\a\n", argv[0] ); return 1; }
   //srand( (uint32_t) time(nullptr) ); //随机种子
   srand( 31415926 ); //固定种子（假种子，调试用）
   Rank s = atoi(argv[1]), t = atoi(argv[2]);
   for ( Rank k = 0; k < t; k++ ) {
      printf( "\n[Test #%d/%d]\n", k, t );
      testVector( s );
   }
   return 0;
}
