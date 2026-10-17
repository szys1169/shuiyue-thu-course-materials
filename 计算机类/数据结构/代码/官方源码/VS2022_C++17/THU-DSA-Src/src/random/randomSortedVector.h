#pragma once

#include "vector/vector.h"

/******************************************************************************************
 * 生成长度为n的随机有序向量，元素取值来自[min, max]
 * The Art of Computer Programming, Vol.2, Algorithm S
 ******************************************************************************************/
Vector<int> randomSortedVector( Rank n, int min, int max );
