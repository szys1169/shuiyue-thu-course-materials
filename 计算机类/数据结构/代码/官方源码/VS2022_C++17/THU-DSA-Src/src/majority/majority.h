#pragma once

template <typename T> bool majority( Vector<T> A, T& maj ) { //众数查找算法：T可比较可判等
   maj = majCandidate( A ); //必要性：选出候选者maj
   return majCheck( A, maj ); //充分性：验证maj是否的确当选
}
