/*DSA*/#include "Huffman_PQ.h"

uint32_t* stat( char* sample_text_file ) { //统计字符出现频率
   uint32_t* freq = new uint32_t[N_CHAR];  //以下统计需随机访问，故以数组记录各字符出现次数
   memset( freq, 0, sizeof(int)*N_CHAR ); //清零
   FILE* fp = fopen( sample_text_file, "r" ); //assert: 文件存在且可正确打开
   for ( char ch; 0 < fscanf( fp, "%c", &ch ); ) //扫描样本文件，统计各字符出现频率
      if ( (0x20 <= ch) && (ch < 0x7F) ) freq[ch - 0x20]++;
   fclose( fp ); return freq;
} //stat
