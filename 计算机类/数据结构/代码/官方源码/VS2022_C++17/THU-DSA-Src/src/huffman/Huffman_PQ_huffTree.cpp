/*DSA*/#include "Huffman_PQ.h"

//HuffForest基于优先级队列实现，兼容三种类型：列表、完全二叉堆、左式堆
//编译前只需设置相应的标志：DSA_PQ_List|DSA_PQ_ComplHeap|DSA_PQ_LeftHeap
HuffTree huffTree( HuffForest& F ) { //由Huffman森林，构造出Huffman编码树
   while ( 1 < F.size() ) { //每迭代一步，森林中都会减少一棵树
      HuffTree T1 = F.delMax(), T2 = F.delMax(), S; //取出权重最小的两棵树，合并成S
      S.insert( HuffChar( ( Weight( T2 ) + Weight( T1 ) ) ) ); //S的权重取作子树权重之和
      S.attach( T2, S.root() ); S.attach( S.root(), T1 ); //T2权重不小于T1
      F.insert( S ); //再插回森林
      /*DSA*/printf( "%2d: Merge(", F.size() ); print( T1.root()->data ); printf( ", " ); print( T2.root()->data ); printf( ")\n" );
      /*DSA*///print( S );
   } //森林中最终唯一所剩的那棵树，即Huffman编码树
   return F.delMax(); //且其层次序列必然单调非增
} //huffmanTree
