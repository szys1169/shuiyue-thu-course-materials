/*DSA*/#include <algorithm>
/*DSA*/using namespace std;
/*DSA*/#include <typeinfo>
/*DSA*/#include "stack/stack.h"
/*DSA*/extern Rank ms, mr, mt; //最大矩形 = H[mr]*(mt-ms)

/*DSA*///借助栈结构，计算直方图H[]中的最大矩形（并列时取最靠左者）
uint64_t mr_STACK( uint64_t H[], Rank n ) { //单趟扫描版
   Stack<Rank> SR; //次栈顶、栈顶总是s[r]-1与r，当前的t = t[r]
   uint64_t maxRect = 0;
   for ( Rank t = 0; t <= n; t++ ) { //对于以t为右限的
      while ( !SR.empty() && ( t == n || H[SR.top()] >= H[t] ) ) { //每一个极大矩形
         Rank r = SR.pop(), s = SR.empty() ? 0 : SR.top() + 1; //次栈顶即是左限
         /*DSA*/if ( maxRect < H[r] * ( t - s ) ) { mr = r; ms = s; mt = t; }
         maxRect = max( maxRect, H[r] * ( t - s ) ); //算出面积，并择优更新
      } //while
      if ( t < n ) SR.push( t ); //栈中只记录所有的H[s] = min{ H[k] | s <= k <= t }
   } //assert( SR.empty() )
   return maxRect;
} //每项进栈、出栈不过常数次，累计成本O(n)
