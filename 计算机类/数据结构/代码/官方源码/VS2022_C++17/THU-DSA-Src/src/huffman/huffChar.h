#pragma once
/*DSA*/#include <algorithm>
/*DSA*/using namespace std;

struct HuffChar { //超字符
   char ch; uint32_t weight; //字符、频数
   HuffChar( uint32_t w = 0, char c = '^' ) : weight( w ), ch( c ) {}; //构造
   HuffChar( HuffChar const& hc ) : weight( hc.weight ), ch( hc.ch ) {}; //复制
   bool operator<( HuffChar const& hc ) { return weight > hc.weight; } //比较器：故意大小颠倒
}; //HuffChar
