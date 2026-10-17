#pragma once

#include <cstdlib>
#include <typeinfo>
#include <ctime> //通常用当前时刻设置随机种子
using Rank = uint32_t;

static Rank dice( Rank range ) { //取随机数：最大范围 = [0, range) = 2^60 - 1 = 0x0FFFFFFFFFFFFFFF
   uint64_t x = RAND_MAX < range ? 
                    (uint64_t)rand() << 45
                  | (uint64_t)rand() << 30
                  | (uint64_t)rand() << 15
                  | (uint64_t)rand()
               :  rand(); 
   return x % range;
}
static Rank dice( Rank lo, Rank hi ) { return lo + dice(hi-lo); }
static float dice( float range ) { return rand() % ( 1000*(int)range ) / (float)1000.; }
static double dice( double range ) { return rand() %( 1000*(int)range ) / (double)1000.; }
static char dice() { return (char)( 32 + rand() % 96 ); }
