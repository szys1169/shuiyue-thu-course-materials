#pragma once

/******************************************************************************************
* BTree输出打印
 ******************************************************************************************/
#include "Bitmap/Bitmap.h" //使用位图记录分支转向

template <typename T> void UniPrint::p( BTree<T>& bt ) { //BTree打印（入口）
   printf( "%s*%d/%d:\n", typeid( bt ).name(), bt._size, bt._root->height ); //基本信息
   Bitmap* leftmosts = new Bitmap; //记录当前节点祖先的方向
   Bitmap* rightmosts = new Bitmap; //记录当前节点祖先的方向
   printBTree( bt._root, 0, true, true, leftmosts, rightmosts ); //输出树状结构
   delete leftmosts; delete rightmosts; printf( "\n" );
}

template <typename T> //BTree打印（递归）
static void printBTree( BTNP<T> bt, int depth, bool isLeftmost, bool isRightmost, Bitmap* leftmosts, Bitmap* rightmosts ) {
   if ( !bt ) return;
   isLeftmost ? leftmosts->set( depth ) : leftmosts->clear( depth ); //设置或清除当前层的拐向标志
   isRightmost ? rightmosts->set( depth ) : rightmosts->clear( depth ); //设置或清除当前层的拐向标志
   int k = bt->child.size() - 1; //找到当前节点的最右侧孩子，并
   printBTree( bt->child[k], depth + 1, false, true, leftmosts, rightmosts ); //递归输出之
   /*DSA*/bool parentOK = false; BTNP<T> p = bt->parent;
   /*DSA*/if ( !p ) parentOK = true;
   /*DSA*/else for ( Rank i = 0; i < p->child.size(); i++ ) if ( p->child[i] == bt ) parentOK = true;
   while ( 0 < k-- ) { //自右向左，输出各子树及其右侧的关键码
      /*DSA*/printf( parentOK ? " " : "X" );
      print( bt->key[k] ); printf( " *>" );
      for ( int i = 0; i < depth; i++ ) //根据相邻各层
         ( leftmosts->test( i ) && leftmosts->test( i + 1 ) || rightmosts->test( i ) && rightmosts->test( i + 1 ) ) //的拐向是否一致，即可确定
            ? printf( "     " )
            : printf( "│    " ); //是否应该打印横向联接线
      if ( ( ( 0 == depth && 1 < bt->key.size() ) || !isLeftmost && isRightmost ) && bt->key.size() - 1 == k )
         printf( "┌─" );
      else if ( ( ( 0 == depth && 1 < bt->key.size() ) || isLeftmost && !isRightmost ) && 0 == k )
         printf( "└─" );
      else
         printf( "├─" );
      print( bt->key[k] ); printf( " (%2d)\n", bt->height );
      printBTree( bt->child[k], depth + 1, 0 == k, false, leftmosts, rightmosts ); //递归输出子树
   }
}
