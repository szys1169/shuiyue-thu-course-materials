/*DSA*/#include "Huffman_PQ.h"

int encode( HuffTable& table, Bitmap& codeString, char* s ) { //按照编码表对Bitmap串编码
   int n = 0; //待返回的编码串总长n
   for ( size_t m = strlen( s ), i = 0; i < m; i++ ) //对明文中的
      if ( ( 0x20 <= s[i] ) && ( s[i] < 0x7F ) ) { //每个字母
         Entry<char, char*>* c = table.get( s[i] ); //取出其对应的编码串
         printf( "%s", c->value ); //输出当前字符的编码
         for ( size_t m = strlen( c->value ), j = 0; j < m; j++ ) //将当前字符的编码接入编码串
            '1' == c->value[j] ? codeString.set( n++ ) : codeString.clear( n++ );
      }
   printf( "\n" ); return n;
} //二进制编码串记录于位图codeString中
