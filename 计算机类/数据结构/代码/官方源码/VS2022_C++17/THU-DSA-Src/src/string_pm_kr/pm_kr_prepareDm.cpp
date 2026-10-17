/*DSA*/#include "pm_kr.h"

HashCode prepareDm( size_t m ) { //预处理：计算R^(m-1) % M （仅需调用一次，不必优化）
   HashCode  Dm = 1;
   for ( size_t i = 1; i < m; i++ ) Dm = ( R*Dm ) % M; //直接累乘m-1次，并取模
   return Dm;
} //prepareDm
