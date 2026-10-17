#pragma once

#define BalFac(x) ( Height( (x)->lc ) - Height( (x)->rc ) ) //平衡因子
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) ) //AVL树平衡条件
