#pragma once

#define ROOT 0
#define L_CHILD 1
#define R_CHILD -1*L_CHILD

template <typename T> //元素类型
void UniPrint::p( PQ_ComplHeap<T>& pq ) { //打印输出PQ_ComplHeap
   printf( "%s*%d:\n", typeid( pq ).name(), pq.size() ); //基本信息
   int branchType[256]; //最深256层 <= 2^256 = 1.16*10^77
   printComplHeap( ( Vector<T>& ) pq, pq.size(), 0, 0, ROOT, branchType ); //树状结构
   printf( "\n" );
}

template <typename T> //元素类型
static void printComplHeap( Vector<T>& elem, int n, int k, int depth, int type, int* bType ) { //递归打印输出
   if ( k >= n ) return; //递归基
   bType[depth] = type;
   printComplHeap( elem, n, RChild( k ), depth + 1, R_CHILD, bType ); //右子树（在上）
   print( elem[k] );( 0 < k ) && ( elem[Parent( k ) ] < elem[k] ) ? printf( "X" ) : printf( " " ); printf( "*" );
   for ( int i = 0; i < depth; i++ ) //根据相邻各层
      if ( bType[i] + bType[i+1] ) //的拐向是否一致，即可确定
         printf( "      " ); //是否应该
      else  printf( "│    " ); //打印横线
   switch( type ) {
      case  R_CHILD  :  printf( "┌─" );  break;
      case  L_CHILD  :  printf( "└─" );  break;
      default        :  printf( "──" );  break; //root
   }
   print( elem[k] );( 0 < k ) && ( elem[Parent( k ) ] < elem[k] ) ? printf( "X" ) : printf( " " ); printf( "\n" );
   printComplHeap( elem, n, LChild( k ), depth + 1, L_CHILD, bType ); //左子树（在下）
}
