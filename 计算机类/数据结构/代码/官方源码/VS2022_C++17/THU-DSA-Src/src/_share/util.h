#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

//测试、演示用小工具
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <typeinfo>

#include "inv_Elem.h"
#include "inv_list.h"
#include "inv_vector.h"

#include "double_Elem.h"
#include "increase_Elem.h"
#include "hailstone_Elem.h"
#include "increase_list.h"
#include "increase_vector.h"

#include "sum_Elem.h"
#include "sum_list.h"
#include "sum_vector.h"

#include "rand.h" //随机数

#define max(a,b) ( ( (a) >(b) ) ? (a) : (b) )
#define min(a,b) ( ( (a) <(b) ) ? (a) : (b) )

#if defined(DSA_DEBUG) //编译开关，控制调试输出
#define DSA(x)  { x } //输出
#else
#define DSA(x) //不输出
#endif
