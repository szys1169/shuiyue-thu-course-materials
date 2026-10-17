/*DSA*/#include "BinNode_inorder.h"
/*DSA*/#include "BinNode_inorder_1.h"
/*DSA*/#include "BinNode_inorder_2.h"
/*DSA*/#include "BinNode_preorder.h"
/*DSA*/#include "BinNode_preorder_1.h"
/*DSA*/#include "BinNode_preorder_2.h"
/*DSA*/#include "BinNode_postorder.h"
/*DSA*/#include "BinNode_postorder_1.h"
/*DSA*/#include "BinNode_levelorder.h"

template <typename T> template <typename V> void BinNode<T>::traverse( V& visit ) {
   Rank method = rand() % 9; //此处暂随机选择，以做测试
   printf( "traversal method #%d\n", method );
   //switch ( 2 ) {
   switch ( method ) {
      case  0 : inorder( this, visit ); break; //中序递归版
      case  1 : inorder1( this, visit ); break; //中序迭代版#1
      case  2 : inorder2( this, visit ); break; //中序迭代版#2
      case  3 : preorder( this, visit ); break; //先序递归版
      case  4 : preorder1( this, visit ); break; //先序迭代版#1
      case  5 : preorder2( this, visit ); break; //先序迭代版#2
      case  6 : postorder( this, visit ); break; //后序递归版
      case  7 : postorder1( this, visit ); break; //后序迭代版
      default : levelorder( this, visit ); //层次
   } //switch
} //traverse
