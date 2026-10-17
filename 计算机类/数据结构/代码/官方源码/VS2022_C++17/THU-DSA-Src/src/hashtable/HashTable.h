#pragma once

/*DSA*/#include "Dictionary/Dictionary.h" //引入词典ADT
/*DSA*/#include "Bitmap/Bitmap.h" //引入位图

template <typename K, typename V> //key、value
class Hashtable : public Dictionary<K, V> { //符合Dictionary接口的Hashtable模板类
   /*DSA*/friend class UniPrint;
private:
   Entry<K, V>** ht; //桶数组，存放词条指针
   Bitmap* removed; //懒惰删除标记位图：总数L = removed->size() = removed->top
   Rank M, N; //桶的总数、词条的数目：(N+L)/M <= Lambda_max
protected:
   Rank probe4Hit( const K& k ); //沿关键码k对应的试探链，找到词条匹配的桶
   Rank probe4Free( const K& k ); //沿关键码k对应的试探链，找到首个可用空桶
   void rehash(); //重散列算法：扩充桶数组，保证装填因子在警戒线以下
public:
   Hashtable( Rank c = 5 ); //创建一个容量不小于c的散列表（为测试暂时选用较小的默认值）
   ~Hashtable(); //释放桶数组及其中各（非空）元素所指向的词条
   Rank size() const { return N; } //当前的词条数目
   Entry<K, V>* get( K ); //读取
   Entry<K, V>* put( K, V ); //插入（词条允许相等；如不允许，调用之前需先get()确认）
   bool remove( K ); //删除
};
/*DSA*/
/*DSA*/#define PRIME_TABLE "../../_input/hashtable/prime-1048576-bitmap.txt"
/*DSA*/#include "Hashtable_constructor.h"
/*DSA*/#include "Hashtable_destructor.h"
/*DSA*/#include "Hashtable_hashCode.h"
/*DSA*/#include "Hashtable_probe4Hit.h"
/*DSA*/#include "Hashtable_probe4Free.h"
/*DSA*/#include "Hashtable_get.h"
/*DSA*/#include "Hashtable_put.h"
/*DSA*/#include "Hashtable_remove.h"
/*DSA*/#include "Hashtable_rehash.h"
