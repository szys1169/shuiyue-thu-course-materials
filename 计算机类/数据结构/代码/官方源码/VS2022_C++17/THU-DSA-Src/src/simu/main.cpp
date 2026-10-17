#include "simu.h"

int delay;

void printCustomer( uint32_t c ) //输出顾客c的状态
{ printf( "%4d", c ); }

int main( int argc, char* argv[] ) { //事件模拟
   if ( argc < 4 ) {  printf( "Usage: %s <nWin> <servTime> <delay(ms)>\n", argv[0] ); return -1;  }
   srand( (uint32_t) time(nullptr) ); //设置随机种子
   delay = atoi( argv[3] );
   simu( atoi( argv[1] ), atoi( argv[2] ) ); //启动模拟
   return 0;
}
