#pragma once

template <typename T> void Vector<T>::unsort( Rank lo, Rank hi ) { //随机置乱区间[lo, hi)
   T* V = _elem + lo; //将子向量_elem[lo, hi)视作另一向量V[0, hi - lo)
   for ( Rank i = hi - lo; 1 < i; --i ) //自后向前
      swap( V[i - 1], V[rand() % i] ); //将V[i - 1]与V[0, i)中某一元素随机交换
}
