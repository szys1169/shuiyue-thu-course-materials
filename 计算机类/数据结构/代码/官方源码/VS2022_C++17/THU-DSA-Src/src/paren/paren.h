#pragma once

#include<iostream>
using namespace std;

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "UniPrint/print.h"

#include "stack/stack.h"

bool paren( const char exp[], Rank n );
void displaySubstring( const char exp[], Rank lo, Rank hi );
void displayProgress( const char exp[], Rank i, Stack<char> S );
