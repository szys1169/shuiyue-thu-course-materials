#pragma once

/*DSA*/template <typename T> void List<T>::traverse( void( *visit ) ( T& ) ) //借助函数指针机制遍历
/*DSA*/  { for ( LNP<T> p = head->succ; p != tail; p = p->succ ) visit( p->data ); }
/*DSA*/
template <typename T> template <typename VST> void List<T>::traverse( VST& visit ) //遍历
   { for ( LNP<T> p = head->succ; p != tail; p = p->succ ) visit( p->data ); }
