#include "hashtable.h"


int naive_hashing::operator()(char* str, int N){
    if(str == NULL) return 0;
    else return (str[0] + N) % N;
}


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