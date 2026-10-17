#pragma once

#pragma warning(disable : 4996 4800)
#include <cstdlib>
#include <cstdio>
#include <memory.h>
/*DSA*/#include <typeinfo>
/*DSA*/using Rank = uint32_t;

class Bitmap { //位图Bitmap类
private:
   unsigned char* M; Rank N, _sz; //数组M共有8*N个bit，其中_sz位已设置
protected:
   void init( Rank n, bool b = false ) //初始化为n个数值为b的bit位
      { M = new uint8_t[N = ( n + 7 ) / 8]; memset( M, 0xFF*b, N ); _sz = 0; }
public:
   Bitmap( Rank n = 8, bool b = false ) { init( n, b ); }
/*DSA*/   Bitmap( char* file, Rank n = 8 ) : Bitmap( n ) { //按指定或默认规模，从指定文件中读取位图
/*DSA*/      FILE* fp = fopen( file, "r" ); fread( M, sizeof( char ), N, fp ); fclose( fp );
/*DSA*/      for ( Rank k = 0, _sz = 0; k < n; _sz += test(k++) );
/*DSA*/   }
   ~Bitmap() { delete[] M; } //析构时释放位图空间
   Rank size() { return _sz; }
   void reset() { memset( M, 0, N ); _sz = 0; } //O(n)，待改进
   bool test ( Rank k ) {    expand(k); return  M[k >> 3]  &  (0x80 >> (k & 0x07)); }
   void set  ( Rank k ) { if ( test(k)) return; M[k >> 3] |=  (0x80 >> (k & 0x07)); _sz++; }
   void clear( Rank k ) { if (!test(k)) return; M[k >> 3] &= ~(0x80 >> (k & 0x07)); _sz--; }
   /*DSA*/void dump( char* file ) //将位图整体导出至指定的文件，以便对此后的新位图批量初始化
   /*DSA*/   { FILE* fp = fopen( file, "w" ); fwrite( M, sizeof( char ), N, fp ); fclose( fp ); }
   /*DSA*/char* bits2string( Rank n ) { //将前n位转换为字符串，n < 8*N
   /*DSA*/   char* s = new char[n + 1]; s[n] = '\0';
   /*DSA*/   for ( Rank i = 0; i < n; i++ ) s[i] = test( i ) ? '1' : '0';
   /*DSA*/   return s;
   /*DSA*/} //bit2string
   void expand( Rank k ) { //若被访问的Bitmap[k]已出界，则需扩容
      if ( k < 8*N ) return; //仍在界内，无需扩容
      Rank oldN = N; unsigned char* oldM = M;
      init( 2*k ); memcpy_s( M, N, oldM, oldN ); //加倍策略
      delete[] oldM;
   } //expand
/*DSA*/
/*DSA*/   void print( Rank n ) //逐位打印以检验位图内容，非必需接口
/*DSA*/   {  expand( n ); for ( Rank i = 0; i < n; i++ ) printf( test( i ) ? "1" : "0" );  }
}; //Bitmap
