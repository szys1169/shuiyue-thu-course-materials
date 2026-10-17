#pragma once

template <typename T> void List<T>::uniquify() { //成批剔除重复元素，效率更高
   if ( _size < 2 ) return; //过短的列表，自然不含相等元素
   for ( LNP<T> p = first(), q = p->succ; q != tail; q = p->succ )
      if ( p->data != q->data ) p = q; //若p与其后继q不等，则前进一步
      else remove( q ); //否则直接删除后者，而不必如向量那样间接删除
} //uniquify()
