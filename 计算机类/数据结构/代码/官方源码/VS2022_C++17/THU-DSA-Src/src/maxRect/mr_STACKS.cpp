/*DSA*/#include <algorithm>
/*DSA*/using namespace std;
/*DSA*/#include <typeinfo>
/*DSA*/#include "stack/stack.h"
/*DSA*/extern Rank ms, mr, mt; //最大矩形 = H[mr]*(mt-ms)

/*DSA*///借助栈结构，计算直方图H[]中的最大矩形（并列时取最靠左者）
uint64_t mr_STACKS( uint64_t H[], Rank n ) { //两趟扫描版
   Stack<Rank> S; Rank* s = new Rank[n]; //单调栈S，左限数组O(n)空间
   for ( Rank r = 0; r < n; r++ ) { //依次检视每根H[r]
      while ( !S.empty() && ( H[S.top()] >= H[r] ) ) S.pop(); //保持单调
      s[r] = S.empty() ? 0 : 1 + S.top(); //确定左限s(r)
      S.push(r); //保持单调
   }
   while ( !S.empty() ) S.pop(); //S使命完成，可以清空

   Stack<Rank> T; Rank* t = new Rank[n]; //单调栈T，右限数组O(n)空间
   for ( Rank r = n-1; -1 != r; r-- ) { //依次检视每根H[r]
      while ( !T.empty() && H[r] <= H[T.top()] ) T.pop(); //保持单调
      t[r] = T.empty() ? n : T.top(); //确定右限t(r)
      T.push(r); //保持单调
   }
   while ( !T.empty() ) T.pop(); //T使命完成，可以清空

   uint64_t maxRect = 0;
   for ( Rank r = 0; r < n; r++ ) //算出每个极大矩形的面积，并择优更新
   /*DSA*/{
      /*DSA*/if ( maxRect <  H[r] * ( t[r] - s[r] ) ) { mr = r; ms = s[r]; mt = t[r]; }
      maxRect = max( maxRect, H[r] * ( t[r] - s[r] ) );
   /*DSA*/}
   delete [] s; delete [] t;
   return maxRect; //最大的极大矩形，即是最大矩形
} //每项进栈、出栈不过常数次，累计成本O(n)
