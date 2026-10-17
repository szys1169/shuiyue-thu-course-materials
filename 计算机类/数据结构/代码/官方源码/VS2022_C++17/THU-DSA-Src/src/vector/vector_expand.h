#pragma once

template <typename T> void Vector<T>::expand( Rank d ) { //扩容
   if ( _size + d <= _capacity ) return; //若足以新增d个元素，则无需扩容
   T* oldElem = _elem; //记下原数据区
   _capacity = (_size + d)*2; //扩容：本次插入之后，装填因子=50%
   _elem = new T[ _capacity ]; //分配新空间
   copy( oldElem, 0, _size ); //转移数据
   delete [] oldElem; //释放原数据区
} //expand
