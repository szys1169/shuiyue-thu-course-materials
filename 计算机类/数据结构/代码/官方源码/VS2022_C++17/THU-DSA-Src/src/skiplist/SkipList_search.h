#pragma once

template <typename T> TowerPosi<T> Skiplist<T>::search( const T& e ) {
   _x = head; //从head塔的顶层出发
   for ( Rank h = height(_x) - 1; -1 != h; h-- ) //逐层下降，直至底层
      while ( ( tower(_x)[h].succ != tail ) && ( key(tower(_x)[h].succ) <= e ) ) //在每一层都
         _x = tower(_x)[h].succ; //尽可能右移
   return _x == head ? nullptr : _x; //不大于e的最后一座塔（head ~ nullptr）
} //search
