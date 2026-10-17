#pragma once
#pragma warning(disable : 4996)

/*DSA*/#include <typeinfo>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include "stack/stack.h" //使用栈
#include "UniPrint/print.h"

uint64_t facI( int n );
double calcu( Stack<double>&, char );
void readNumber( char*, Stack<double>& );
double rpn( char* S );
