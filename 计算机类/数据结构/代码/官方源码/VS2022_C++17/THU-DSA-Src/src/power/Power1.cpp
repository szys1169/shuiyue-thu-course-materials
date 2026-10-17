/*DSA*/#include <typeinfo>

uint64_t power( uint64_t a, int n ) {
   uint64_t pow = 1, p = a;
   while ( 0 < n ) { //O(logn)
      if ( n & 1 )
         pow *= p; //O(1)？
      n >>= 1; //O(1)？
      p *= p; //O(1)？
   }
   return pow;
} //高效版，O(logn)
