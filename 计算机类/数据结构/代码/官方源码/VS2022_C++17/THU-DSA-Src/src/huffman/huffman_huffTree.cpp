/*DSA*/#include "huffman_PQ.h"

HuffTree huffTree( HuffForest& forest ) { //由Huffman森林，构造出Huffman编码树
   while ( 1 < forest.size() ) { //每迭代一步，森林中都会减少一棵树
      HuffTree T1 = forest.remove( forest.getMax() ),
               T2 = forest.remove( forest.getMax() ); //取出权重最小的两棵树
      /*DSA*/printf( "Merging " ); print( T1.root()->data ); printf( " with " ); print( T2.root()->data ); printf( " ...\n" );
      HuffTree S; //将其合并成一棵新树
      S.insert( HuffChar( T1.root()->data.weight + T2.root()->data.weight ) );
      S.attach( T2, S.root() ); S.attach( S.root(), T1 ); //右大左小
      forest.insertLast( S ); //再插回至森林
   } //森林中最终唯一所剩的那棵树，即Huffman编码树
   return forest.first()->data; //且层次序列必然单调非增
} //huffTree
