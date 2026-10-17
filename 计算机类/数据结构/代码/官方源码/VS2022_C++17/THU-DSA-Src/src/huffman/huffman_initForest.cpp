/*DSA*/#include "Huffman_PQ.h"

HuffForest initForest( uint32_t* freq ) { //根据频率统计表，为每个字符创建一棵树
   HuffForest forest; //以List实现Huffman森林
   for ( char i = 0x20; i < 0x7F; i++ ) { 
      HuffTree T; T.insert( HuffChar( freq[i-0x20], i ) ); //每个字符自成一棵树
      forest.insertLast( T ); //整体构成森林
   }
   return forest;
} //initForest
