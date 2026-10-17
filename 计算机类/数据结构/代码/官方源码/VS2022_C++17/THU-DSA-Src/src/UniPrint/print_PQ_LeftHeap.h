#pragma once

template <typename T> void UniPrint::p( PQ_LeftHeap<T>& lh ) { //打印输出PQ_LeftHeap
   p( ( BinTree<T>& ) lh );
}
