#pragma once
#pragma warning(disable : 4996)

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <typeinfo>

#include "stack/stack.h" //使用栈
#include "priority.h" //优先级快查表

uint64_t facI( int n );
double calcu( Stack<double>&, char );
void displayProgress( char*, char*, Stack<double>&, Stack<char>&, char* );
void readNumber( char*&, Stack<double>& );
Operator optr2rank( char );
char prio( char, char );
void append( char*, double ); //重载
void append( char*, char ); //重载
double evaluate( char* expr, char* rpn );
