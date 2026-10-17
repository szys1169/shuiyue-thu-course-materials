#pragma once

/******************************************************************************************
* 二叉树输出打印
 ******************************************************************************************/
#include "Bitmap/Bitmap.h" //使用位图记录分支转向

#define ROOT 0
#define L_CHILD 1
#define R_CHILD -1*L_CHILD

template <typename T> void UniPrint::p( BinTree<T>& bt ) { //基础BinTree
   printf( "%s*%d/%d:\n", typeid( bt ).name(), bt.size(), bt.root() ? bt.root()->height : -1 ); //基本信息
   Bitmap branchType; //记录当前节点祖先的方向
   printBinTree( bt.root(), -1, ROOT, &branchType ); //树状结构
   printf("\n");
}

template <typename T> void UniPrint::p( BST<T>& bst ) { //基于BinTree实现的BST
   printf( "%s*%d/%d:\n", typeid( bst ).name(), bst.size(), bst.root() ? bst.root()->height : -1 ); //基本信息
   Bitmap branchType; //记录当前节点祖先的方向
   printBinTree( bst.root(), -1, ROOT, &branchType ); //树状结构
   printf("\n");
}

template <typename T> void UniPrint::p( AVL<T>& avl ) { //基于BST实现的AVL
   printf( "%s*%d/%d:\n", typeid( avl ).name(), avl.size(), avl.root() ? avl.root()->height : -1 ); //基本信息
   Bitmap branchType; //记录当前节点祖先的方向
   printBinTree( avl.root(), -1, ROOT, &branchType ); //树状结构
   printf("\n");
}

template <typename T> void UniPrint::p( RedBlack<T>& rbt ) { //基于BST实现的RedBlack
   printf( "%s*%d/%d:\n", typeid( rbt ).name(), rbt.size(), rbt.root() ? rbt.root()->height : 0 ); //基本信息
   Bitmap branchType; //记录当前节点祖先的方向
   printBinTree( rbt.root(), -1, ROOT, &branchType ); //树状结构
   printf("\n");
}

template <typename T> void UniPrint::p( Splay<T>& spl ) { //基于BST实现的Splay
   printf( "%s*%d/%d:\n", typeid( spl ).name(), spl.size(), spl.root() ? spl.root()->height : -1 ); //基本信息
   Bitmap branchType; //记录当前节点祖先的方向
   printBinTree( spl.root(), -1, ROOT, &branchType ); //树状结构
   printf("\n");
}

// 二叉树各种派生类的统一打印
template <typename T> void printBinTree( BNP<T> t, int depth, int type, Bitmap* bType ) {
   if ( !t ) return;
   if ( -1 < depth ) //设置当前层的拐向标志
      R_CHILD == type ? bType->set( depth ) : bType->clear( depth );
   printBinTree( t->rc, depth + 1, R_CHILD, bType ); //右子树（在上）
   print( t ); printf( " *" );
   for ( int i = -1; i < depth; i++ ) //根据相邻各层
      if ( ( 0 > i ) || bType->test( i ) == bType->test( i + 1 ) ) //的拐向是否一致，即可确定
         printf( "      " ); //是否应该
      else  printf( "│     " ); //打印横线
   switch( type ) {
      case  R_CHILD  :  printf( "┌─" );  break;
      case  L_CHILD  :  printf( "└─" );  break;
      default        :  printf( "──" );  break; //root
   }
   print( t );
#if defined(DSA_HUFFMAN)
   if ( IsLeaf( t ) ) bType->print( depth + 1 ); //输出Huffman编码
#endif
   printf( "\n" );
   printBinTree( t->lc, depth + 1, L_CHILD, bType ); //左子树（在下）
}
