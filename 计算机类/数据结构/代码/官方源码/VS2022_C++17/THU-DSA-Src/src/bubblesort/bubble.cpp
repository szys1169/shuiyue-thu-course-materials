/*DSA*/#include "_share/util.h"
/*DSA*/#include "UniPrint/print_int_array.h"

void bubblesort( int A[], int n ) {
   /*DSA*/int cmp = 0, swp = 0;
   while ( 1 < n-- ) /*DSA*/{ //做n-1趟起泡扫描
      for ( int i = 0; i < n; i++ ) /*DSA*/{ //逐对检视相邻元素
         if ( A[i] > A[i + 1] ) /*DSA*/{ //一旦发现逆序
            swap( A[i], A[i + 1] ); //随即交换
            /*DSA*/ swp++; printf( "%3d: ", n ); print( A, n, i, i + 2 );
         /*DSA*/}
         /*DSA*/ cmp++;
      /*DSA*/}
   /*DSA*/}
   /*DSA*/printf( "#comparison = %d, #swap = %d\n", cmp, swp );
} //bubblesort
