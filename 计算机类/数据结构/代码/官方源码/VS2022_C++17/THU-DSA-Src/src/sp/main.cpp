/*DSA*/#include "sp.h"

int main( int argc, char* argv[] ) {
   if ( 2 > argc ) {  cout << "Usage: " << argv[0] << "<#item>" << endl; return 1;  }
   srand( (uint32_t) time(nullptr) ); //随机种子
   //srand( 31415926 ); //固定种子（假种子，调试用）
   for ( Rank n = atoi( argv[1] ); ;  ) {
      Vector<Rank> SP;
      for ( Rank r = 1; r < n+1; r++ )
         SP.insert( r );
      SP.unsort();
      print(SP);
      Rank r = spCheck( SP );
      if ( n > r )
         printf( "Jammed at [%d] = %d\n\n\n", r+1, SP[r] );
      else
         { printf( "OK\n" ); break; }
   }
   return 0;
}
