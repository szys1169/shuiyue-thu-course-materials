#pragma once

template <typename T> struct DEPQ : public PQ<T> { //Double-Ended Priority Queue
   virtual T getMin() = 0; //get the element with the lowest priority
   virtual T delMin() = 0; //remove the element with the lowest priority
}; //DEPQ
