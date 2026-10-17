#pragma once

#if defined(DSA_STACK_VECTOR)
#include "stack_vector/stack_vector.h" //由向量派生的栈
#elif defined(DSA_STACK_LIST)
#include "stack_list/stack_list.h" //由列表派生的栈
#else
#endif
