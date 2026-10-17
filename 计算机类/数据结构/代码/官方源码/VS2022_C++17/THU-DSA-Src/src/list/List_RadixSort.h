#pragma once

using U = uint32_t; //约定：类型T或就是U；或可转换为U，并依此定序

template <typename T> void List<T>::radixSort( LNP<T> h, LNP<T> t ) {
   /*DSA*///printf( "RadixSort ...\n" );
   Rank i = 0, n = *t - h - 1; //节点总数
   for ( U radixBit = 0x1; radixBit; radixBit <<= 1 ) //反复地根据当前基数位
      for ( LNP<T> p = h + (i = 0); i < n; i++ ) //将所有节点分拣为前缀（0）与后缀（1）
         ( radixBit & U (p->succ->data) ) ? p->succ->movePred( t ) : p = p->succ;
} //radixSort
