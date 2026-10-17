#pragma once

#include "Vector/Vector.h" //借助多重继承机制，基于向量
#include "DEPQ/DEPQ.h" //按照优先级队列ADT实现的

template <typename T> class SMMH : public DEPQ<T>, public Vector<T> { //Symmetric Min-Max Heap
   /*DSA*/friend class UniPrint; //For test. Just remove this line for real applications
protected:
   //void heapify( Rank n ); //Floyd's heapification
public:
   SMMH() { insert( (T) -1); } //initialized with a dummy root
   void insert( T ); //insert an element(duplicates accepted)
   T getMin() { return _elem[1]; }
   T& getMax() { return _size < 3 ? _elem[1] : _elem[2]; }
   T delMin();
   T delMax();
}; //SMMH
/*DSA*/
/*DSA*/#include "DEPQ_SMMH_macro.h"
/*DSA*/#include "DEPQ_SMMH_Insert.h"
/*DSA*/#include "DEPQ_SMMH_delMin.h"
/*DSA*/#include "DEPQ_SMMH_delMax.h"
/*DSA*///#include "DEPQ_SMMH_heapify.h"
