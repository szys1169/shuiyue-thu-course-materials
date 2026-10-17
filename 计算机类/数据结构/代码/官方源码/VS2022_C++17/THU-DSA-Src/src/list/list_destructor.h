#pragma once

template <typename T> List<T>::~List() { //从head到tail，逐个释放每个节点
   //*DSA*/printf( "Destruct: %s\n", typeid(*this).name() );
   for ( LNP<T> x = head; x != tail; delete (x = x->succ)->pred );
   delete tail;
} //时间复杂度线性正比于节点总数，以及每个T类型对象的递归析构所需的时间
