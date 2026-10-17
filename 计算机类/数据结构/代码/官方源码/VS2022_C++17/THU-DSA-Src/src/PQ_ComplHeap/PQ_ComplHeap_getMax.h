#pragma once

template <typename T> T& PQ_ComplHeap<T>::getMax() { return _elem[0]; } //取优先级最高的词条
