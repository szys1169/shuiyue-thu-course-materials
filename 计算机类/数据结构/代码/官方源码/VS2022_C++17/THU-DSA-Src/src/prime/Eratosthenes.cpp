#include "Bitmap/Bitmap.h" //引入Bitmap结构
/*DSA*/ #include "_share/util.h"
/*DSA*/// 筛法求素数：找出小于n的所有素数
/*DSA*/// 内循环每趟迭代O(n/i)步，外循环由素数定理至多n/ln(n)趟，累计耗时不过
/*DSA*///       n/2 + n/3 + n/5 + n/7 + n/11 + ...
/*DSA*///    <  n/2 + n/3 + n/4 + n/6 + n/7 + ... + n/(n/ln(n))
/*DSA*///    =  O(n(ln(n/ln(n)) - 1))
/*DSA*///    =  O(nln(n) - nln(ln(n)) - 1)
/*DSA*///    =  O(nlog(n))
/*DSA*/// 如下实现中，内循环的起点、外循环的终点都了优化
void eratosthenes( Rank n, char* file ) {
   Bitmap B( n, true ); B.clear( 0 ); B.clear( 1 ); //0和1都不是素数
   for ( Rank i = 2; i*i < n; i++ ) //逐个地
      if ( B.test( i ) ) //确认下一个素数i
         for ( Rank j = i*i; j < n; j += i ) //并将一系列能被i整除的
            B.clear( j ); //j标记为合数（小于i*i的合数，必在此之前已被标记）
   B.dump( file ); //将筛选标记统一存入指定文件，以便日后直接导入
} //eratosthenes
