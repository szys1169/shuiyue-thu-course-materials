#pragma once

template <typename T> void Vector<T>::shrink() { //装填因子过小时压缩向量所占空间
   if ( _capacity < DEFAULT_CAPACITY * 2 ) return; //不致收缩到DEFAULT_CAPACITY以下
   if ( _size * 4 > _capacity ) return; //以25%为界
   T* oldElem = _elem; _elem = new T[_capacity >>= 1]; //容量减半
   copy( oldElem, 0, _size ); //转移数据
   delete[] oldElem; //释放原空间
} //shrink
