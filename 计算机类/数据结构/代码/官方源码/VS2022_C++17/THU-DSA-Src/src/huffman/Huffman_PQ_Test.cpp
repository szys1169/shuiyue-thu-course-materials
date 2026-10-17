/*DSA*/#include "Huffman_PQ_test.h"

/******************************************************************************************
 * 无论编码森林由列表、完全堆还是左式堆实现，本测试过程都可适用
 * 编码森林的实现方式采用优先级队列时，编译前对应的工程只需设置相应标志：
 *    DSA_PQ_List、DSA_PQ_ComplHeap或DSA_PQ_LeftHeap
 ******************************************************************************************/
int main( int argc, char* argv[] ) { //Huffman编码算法统一测试
   /*DSA*/if ( 3 > argc ) { printf( "Usage: %s <sample-text-file> <message#1> [message#2] ...\a\n", argv[0] ); return -1; }
   uint32_t* freq = stat( argv[1] ); //根据样本文件，统计各字符的出现频率
   for ( char i = 0x20; i < 0x7F; i++ ) //输出编码表
      printf( " %c: %d\n", i, freq[ i - 0x20 ] );
   HuffForest forest = initForest( freq ); delete freq; //创建Huffman森林
   HuffTree tree = huffTree( forest ); print( tree ); //构造Huffman编码树
   levelorder( tree.root(), visit() ); printf("\n\n"); //验证：层次遍历序列中，各节点的权重单调非增
   HuffTable table = huffCodeTable( tree ); //将Huffman编码树转换为编码表
   //printf("\n\n");
   //for ( char i = 0x20; i < 0x7F; i++ ) //输出编码表
   //   printf( " %c: %s\n", i, table.get( i )->value );
   for ( int i = 2; i < argc; i++ ) { //对于命令行传入的每一明文串
      /*DSA*/printf( "\nEncoding: %s\n", argv[i] ); //以下测试编码
      Bitmap codeString; //二进制编码串
      int n = encode( table, codeString, argv[i] ); //将根据编码表生成（长度为n）
      /*DSA*/printf( "%s\n", codeString.bits2string( n ) ); //输出该编码串
      /*DSA*/printf( "Decoding: " ); //以下测试解码
      decode( tree, codeString, n ); //利用Huffman编码树，对长度为n的二进制编码串解码
   }
   return 0;
} //main
