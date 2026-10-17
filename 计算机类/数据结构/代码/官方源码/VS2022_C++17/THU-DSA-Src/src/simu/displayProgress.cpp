#include "simu.h"

void displayProgress( Queue<int> window[], int wins, int duration ) {
   system( "cls" ); //清屏
   printf( "============  %4d  ============\n", duration );
   for ( int i = 0; i < wins; i++ ) //对每个窗口，分别
      { print( window[i] ); printf("\n"); }
} //displayProgress
