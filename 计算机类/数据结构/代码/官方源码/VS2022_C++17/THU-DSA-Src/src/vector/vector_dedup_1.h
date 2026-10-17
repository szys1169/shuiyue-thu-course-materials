#pragma once

template <typename T> int Vector<T>::dedup() { //删除无序向量中重复元素（繁琐版）
   int i = -1; //从最前端开始
   while ( ++i < _size - 1 ) { //从前向后，逐一
      int j = i + 1; //assert: _elem[0, i]中不含重复元素
      while ( j < _size )
         if ( _elem[i] == _elem[j] ) remove( j ); //若雷同，则删除后者
         else j++; //并继续扫描
   }
} //dedup
