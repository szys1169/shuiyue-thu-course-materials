#include "hashtable.h"

// hashtable.cpp: 各策略的简单实现

// naive_hashing: 非常简单的示例哈希函数，仅以字符串首字符与表大小做简单计算。
//  - 参数：str（输入字符串），N（哈希表大小）
//  - 返回：一个范围在 [0, N) 内的整数，表示初始哈希位置
// 注意：真实应用应使用更成熟的哈希算法（例如 djb2、FNV、std::hash 等）以减少冲突。
int naive_hashing::operator()(char* str, int N){
    if(str == NULL) return 0;
    else return (str[0] + N) % N;
}

// linear_probe: 线性探测算法实现
//  - operator(): 仅返回下一个槽位 (last_choice + 1) % table_size
//  - init(): 此策略无状态，因此 init 不做任何操作
int linear_probe::operator()(hash_entry* Table, int table_size, int last_choice){
    return (last_choice + 1) % table_size;
}
void linear_probe::init(){
    return; // 无需初始化
}

int bad_hashing::operator()(char* str, int N)
{
    if(str == NULL) return 0;
    long long hash = 0;
    for(int i = 0; str[i] != '\0'; i++) 
    {
        hash = (hash + str[i]) % N;
    }
    return hash;
}

int good_hashing::operator()(char* str, int N)
{
    if(str == NULL) return 0;
    unsigned long hash = 5381;
    int c;
    for (int i = 0 ; str[i] != '\0'; i++) 
    {
        hash = hash * 33  + str[i]; // hash * 33 + c
    }
    return static_cast<int>(hash % N);
}



// 双向平方试探实现
void double_quadratic_probe::init() 
{
    step = 0; 
    is_add = true; 
}


int double_quadratic_probe::operator()(hash_entry* Table, int table_size, int last_choice) 
{
    int offset = step * step;
    int next_pos;
    
    if(is_add == 1) 
    {
        next_pos = (last_choice + offset) % table_size;
        is_add = false; 
    } else 
    {
        next_pos = (last_choice - offset + table_size) % table_size;
        is_add = true; 
        step++; 
    }
    
    return next_pos;
}

// 公共溢出区策略实现
void common_overflow_area::init() 
{
     overflow_idx = 0; 
}

int common_overflow_area::get_main_size(int table_size) 
{
    int main_sz = static_cast<int>(table_size * 0.8);
    return main_sz; // 主表80%，溢出区20%
}

int common_overflow_area::operator()(hash_entry* Table, int table_size, int last_choice) 
{
    int main_sz = get_main_size(table_size);
    int pos = main_sz + (overflow_idx++ % (table_size - main_sz));
    return pos;
}