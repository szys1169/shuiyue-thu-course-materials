/*DSA*/#include <typeinfo>

uint64_t powerBF( uint64_t a, int n ) {
   uint64_t pow = 1;
   while ( 0 < n ) {
      pow *= a;
      n--;
   }
   return pow;
} //蛮力版，O(n)
