#pragma once

/*DSA*/#include <algorithm>
/*DSA*/using namespace std;

/*DSA*/using Rank = uint32_t;
template <typename T> struct BinNode;
template <typename T> using BNP = BinNode<T>*; //节点位置|Binary Node Position

template <typename T> struct BinNode {
   T data;  BNP<T> parent, lc, rc; //数据、父节点及左、右孩子
   int height; //常规二叉树的高度、红黑树的黑高度、左式堆的npl
   bool color; //红黑树节点的颜色（0红、1黑）
//构造方法
   BinNode( T e, BNP<T> _p = nullptr, BNP<T> lc = nullptr,
            BNP<T> rc = nullptr, int h = 0, bool c = 0 )
      : data(e), parent(_p), lc(lc), rc(rc), height(h), color(c)
      { if (lc) lc->parent = this; if (rc) rc->parent = this; }
//操作接口
   Rank size(); //后代总数
   int updateHeight(); //更新高度
   void updateHeightAbove(); //更新当前节点及历代祖先的高度
   BNP<T> insertLc( const T& ); //插入左孩子
   BNP<T> insertRc( const T& ); //插入右孩子
   void attachLc( BNP<T> ); //接入左子树
   void attachRc( BNP<T> ); //接入右子树
   BNP<T> succ(); //直接后继：取决于具体的遍历规则，默认为中序
   template <typename V> void traverse( V& ); //遍历
//比较器、判等器：仅示例各一，其余可自行补充
   bool operator<  ( BinNode const & bn ) { return data <  bn.data; }
   /*DSA*/bool operator<= ( BinNode const & bn ) { return data <= bn.data; }
   /*DSA*/bool operator>  ( BinNode const & bn ) { return data >  bn.data; }
   /*DSA*/bool operator>= ( BinNode const & bn ) { return data <= bn.data; }
   bool operator== ( BinNode const & bn ) { return data == bn.data; } //相等者，未必相同
   /*DSA*/
   /*DSA*/BNP<T> zig(); //顺时针旋转
   /*DSA*/BNP<T> zag(); //逆时针旋转
   /*DSA*/BNP<T> balance(); //完全平衡化
   /*DSA*/BNP<T> imitate( const BNP<T> ); //临摹
}; //BinNode
/*DSA*/
/*DSA*/#include "BinNode_macro.h"
/*DSA*/#include "BinNode_size.h" //后代数目
/*DSA*/#include "BinNode_insert.h" //插入
/*DSA*/#include "BinNode_attach.h" //接入
/*DSA*/#include "BinNode_succ.h" //取节点后继
/*DSA*/#include "BinNode_traverse.h" //遍历
/*DSA*/#include "BinNode_zig.h" //顺时针旋转
/*DSA*/#include "BinNode_zag.h" //逆时针旋转
/*DSA*/#include "BinNode_stretchByZig.h"
/*DSA*/#include "BinNode_stretchByZag.h"
/*DSA*/
/*DSA*/#if defined( DSA_REDBLACK )
/*DSA*/#include "../redBlack/BinNode_updateHeight.h" //红黑树的高度更新规则
/*DSA*///#elif defined( DSA_PQ_LEFTHEAP )
/*DSA*/   //左式堆的高度，只会手工更新
/*DSA*/#else
/*DSA*/#include "BinNode_updateHeight.h" //其余BST的高度更新规则
/*DSA*/#endif
/*DSA*/
