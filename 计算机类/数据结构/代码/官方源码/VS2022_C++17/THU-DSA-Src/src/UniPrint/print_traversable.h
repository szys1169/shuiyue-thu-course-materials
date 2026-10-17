#pragma once

template <typename T> void UniPrint::p( T& s ) { //向量、列表等支持traverse()遍历操作的线性结构
   printf( "%s*%d:\n", typeid( s ).name(), s.size() );
   //printf( "%s[%d]*%d:\n", typeid( s ).name(),(int) &s, s.size() ); //给出结构的id（物理地址）
   s.traverse( print ); //通过print()遍历输出所有元素
   printf( "\n" );
}
