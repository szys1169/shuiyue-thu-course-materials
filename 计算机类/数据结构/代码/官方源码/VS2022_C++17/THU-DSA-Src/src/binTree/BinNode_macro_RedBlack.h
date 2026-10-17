#pragma once

#define RBT_BLACK 1
#define RBT_RED   0
#define Color(x) ( (x) ? (x)->color : RBT_BLACK ) //nullptr视作黑节点
#define IsBlack(x) Color(x) //黑 = true
#define IsRed(x) ( !Color(x) ) //红 = false
#define HeightL(x) ( Height( (x)->lc ) + Color( (x)->lc ) )
#define HeightR(x) ( Height( (x)->rc ) + Color( (x)->rc ) )
#define RbtBalanced(x) ( !(x) || ( HeightL(x) == HeightR(x) ) ) //红黑树平衡条件
