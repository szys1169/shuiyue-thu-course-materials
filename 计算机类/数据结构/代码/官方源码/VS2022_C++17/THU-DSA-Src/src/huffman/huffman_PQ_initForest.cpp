/*DSA*/#include "Huffman_PQ.h"

/******************************************************************************************
 * 初始化Huffman森林：根据传入的频率统计表freq，为每个字符创建一棵树
 ******************************************************************************************
 * forest基于优先级队列实现，此算法适用于符合PQ接口的任何实现方式
 * 为Huffman_PQ_List、Huffman_PQ_ComplHeap和Huffman_PQ_LeftHeap共用
 * 编译前对应工程只需设置相应标志：DSA_PQ_List、DSA_PQ_ComplHeap或DSA_PQ_LeftHeap
 ******************************************************************************************/
HuffForest initForest( uint32_t* freq ) {
   HuffForest forest; //以PQ实现的Huffman森林
   for ( char i = 0x20; i < 0x7F; i++ ) { //为每个字符生成一棵树，并插入森林
      BinTree<HuffChar> T; T.insert( HuffChar( freq[i-0x20], i ) );
      forest.insert( T );
   }
   return forest;
}
/*DSA*///课后：实现PQ_ComplHeap和PQ_LeftHeap的Robert Floyd算法，将本算法的效率提高至O(n)
