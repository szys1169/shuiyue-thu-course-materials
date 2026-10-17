#pragma once

#define IsLChild(x) ( (x)->parent && ( (x) == (x)->parent->lc ) ) //树根不视作左孩子
#define IsLeaf(x) ( !(x)->lc && !(x)->rc ) //是否叶子
#define Sibling( x ) ( (x) == (x)->parent->lc ? (x)->parent->rc : (x)->parent->lc ) //兄弟
#define Uncle( x ) ( Sibling( (x)->parent ) ) //叔叔
#define FromParentTo( x ) /*来自父亲的引用（根节点对应于_root）*/ \
   ( (x)->parent ? ( (x) == (x)->parent->lc ? (x)->parent->lc : (x)->parent->rc ) : _root )
