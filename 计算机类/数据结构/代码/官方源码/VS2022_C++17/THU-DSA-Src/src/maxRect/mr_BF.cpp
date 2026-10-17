/*DSA*/#include <algorithm>
/*DSA*/using namespace std;
/*DSA*/#include <typeinfo>
/*DSA*/using Rank = uint32_t;
/*DSA*/extern Rank ms, mr, mt; //最大矩形 = H[mr]*(mt-ms)

uint64_t mr_BRUTE( uint64_t H[], Rank n ) { //蛮力版
   uint64_t maxRect = 0;
   for ( Rank r = 0, s = 0, t = 0; r < n; r++, s = t = r ) { //由定义
      do s--; while ( (-1 != s) && (H[s] >= H[r]) ); s++; //顺序查找到左限，O(n)
      do t++; while ( (t < n) && (H[r] <= H[t]) ); //顺序查找到右限，O(n)
      /*DSA*/if ( maxRect < H[r] * ( t - s ) ) { mr = r; ms = s; mt = t; }
      maxRect = max( maxRect, H[r] * ( t - s ) ); //算出极大矩形的面积，并择优更新
   }
   return maxRect; //极大矩形中的最大者，即是全局的最大者
} //每个极大矩形耗时O(n)，累计O(n^2)
