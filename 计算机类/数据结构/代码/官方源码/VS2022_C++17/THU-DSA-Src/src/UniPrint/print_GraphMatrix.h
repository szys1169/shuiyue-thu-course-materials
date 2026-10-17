#pragma once

template <typename Tv, typename Te> //顶点类型、边类型
void UniPrint::p( GraphMatrix<Tv, Te>& s ) { //图Graph
   Rank inD = 0; for ( Rank i = 0; i < s.n; i++ ) inD += s.inDegree( i );
   Rank outD = 0; for ( Rank i = 0; i < s.n; i++ ) outD += s.outDegree( i );
   printf( "%s*(%d, %d):\n", typeid( s ).name(), s.n, s.e ); //基本信息：[%d] ~ (int) &s
//标题行
   print( s.n ); printf( " " ); print( inD ); printf( "|" );
   for ( Rank i = 0; i < s.n; i++ ) { print( s.vertex( i ) ); printf( "[" ); print( s.status( i ) ); printf( "] " ); }
   printf( "\n" );
//标题行（续）
   print( outD ); printf( " " ); print( s.e ); printf( "|" );
   for ( Rank i = 0; i < s.n; i++ ) { print( s.inDegree( i ) ); printf( " " ); }
   printf( "| dTime fTime Parent Weight\n" );
//水平分隔线
   printf( "-----------+" ); for ( Rank i = 0; i < s.n; i++ ) printf( "------" );
   printf( "+----------------------------\n" );
//逐行输出各顶点
   for ( Rank i = 0; i < s.n; i++ ) {
      print( s.vertex( i ) ); printf( "[" ); print( s.status( i ) ); printf( "] " ); print( s.outDegree( i ) ); printf( "|" );
      for ( Rank j = 0; j < s.n; j++ )
         if ( s.exists( i, j ) ) { print( s.edge( i, j ) ); print( s.type( i, j ) ); }
         else printf( "     ." );
      printf( "| " ); print( s.dTime( i ) ); printf( " " ); print( s.fTime( i ) );
      printf( "     " ); if ( -1 == s.parent( i ) ) print( "^" ); else print( s.vertex( s.parent( i ) ) );
      printf( "  " ); if ( INT_MAX > s.priority( i ) ) print( s.priority( i ) ); else print( " INF" );
      printf( "\n" );
   }
   printf( "\n" );
}
