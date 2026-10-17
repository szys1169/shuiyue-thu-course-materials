/*DSA*/#include <typeinfo>

#include<iostream>
using namespace std;

uint64_t powerBF( uint64_t, int );
uint64_t power( uint64_t, int );
uint64_t power2BF_I( int );
uint64_t power2_I( int );
uint64_t power2BF( int );
uint64_t power2( int );

int main( int argc, char* argv[] ) { //测试Power
   uint64_t a; int r;
   if ( 3 > argc ) {  cout << "Usage: " << argv[0] << "<base><exponent>" << endl; return 1;  } //检查参数
   a = _atoi64( argv[1] ); r = atoi( argv[2] ); //获取输入
   printf( "\n2 ^ %d  =  %I64d  =  %I64d\n\n", r, power2BF_I( r ), power2_I( r ) ); //迭代版
   printf( "\n2 ^ %d  =  %I64d  =  %I64d\n\n", r, power2BF( r ), power2( r ) ); //递归版
   printf( "\n%I64d ^ %d  =  %I64d  =  %I64d\n\n", a, r, powerBF( a, r ), power( a, r ) ); //通用算法迭代版
   return 0;
}
