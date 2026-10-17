#pragma once

template <typename T> T& PQ_LeftHeap<T>::getMax() { return _root->data; } //堆顶即是最大词条
