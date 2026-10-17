#pragma once

#define Parent( i )         ( ( (i) - 1 ) >> 1 ) //PQ[i]的父节点（可能越界）
#define LChild( i )         ( 1 + ( (i) << 1 ) ) //PQ[i]的左孩子（可能越界）
#define RChild( i )         ( ( 1 + (i) ) << 1 ) //PQ[i]的右孩子（可能越界）
#define LC( n, i )          ( LChild(i) < (n) ? LChild(i) : (i) ) //左孩子（没有时，自己权当）
#define RC( n, i )          ( RChild(i) < (n) ? RChild(i) : (i) ) //右孩子（没有时，自己权当）
#define Bigger( PQ, i, j )  ( ( PQ[i] < PQ[j] ) ? (j) : (i) ) //更大者（等时前者优先）
#define ProperParent( PQ, n, i ) /*i及其孩子中的最大者（无论有无孩子，无论几个孩子）*/ \
        Bigger( (PQ), (i), Bigger( (PQ), LC( (n), (i) ), RC( (n), (i) ) ) )
