#include <cstring>
#include <cstdio>
#include<iostream>
/*
 * hashtable.h
 * 一个非常简单的开放寻址哈希表示例（C++ 风格但没有使用 STL）。
 * 本文件包含：
 *  - hash_entry：用于存储 key（C 字符串）和 value（int）的条目
 *  - hashing_strategy：哈希函数接口（策略模式）
 *  - naive_hashing：一个示例哈希函数实现（非常简单，仅演示）
 *  - collision_strategy：冲突处理策略接口（例如线性探测）
 *  - linear_probe：线性探测实现
 *  - hashtable：哈希表主体，使用传入的哈希策略和冲突策略
 *
 * 说明与注意事项：
 *  - 本实现为教学/实验用途，未处理所有边界情况（如表满时的行为、负载因子调整、删除标记等）。
 *  - hash_entry 会在构造时为字符串分配内存（new char[...]），因此在实际完整实现中需要正确释放（本示例中简化处理）。
 *  - hashtable 使用指针保存策略对象（hashing_strategy*、collision_strategy*），调用者负责策略对象的生命周期管理。
 */

const int TABLE_SIZE = 499883; // = 124970 * 4 + 3 （只是一个常量示例，实际 hashtable 构造函数接受 size 参数）

struct hash_entry{
    char* my_string; // 指向堆上分配的 C 字符串，NULL 表示该槽为空
    int my_data;     // 与键关联的整数数据
    hash_entry(){
        my_string = NULL; my_data = 0;
    }
    // 构造函数：深拷贝输入字符串到新分配的内存
    hash_entry(char* str, int data):my_data(data){
        my_string = new char[strlen(str)+1];
        strcpy(my_string, str);
    }
};

// 哈希函数抽象接口：输入字符串和表大小，返回初始槽位置 [0, N)
struct hashing_strategy{
    virtual int operator()(char* str, int N) = 0;
};

// 一个很简单的示例哈希函数实现（仅演示策略模式）
struct naive_hashing: public hashing_strategy{
    int operator()(char* str, int N) override;
};

// 冲突解决策略抽象接口：可维护内部状态（通过 init 重置）
// operator() 接受表、表大小和上一次选择的位置，返回下一个尝试的位置
struct collision_strategy{
    virtual void init() = 0; // 初始化/重置内部状态（每次开始查找/插入前调用）
    virtual int operator()(hash_entry* Table, int table_size, int last_choice) = 0;
};

// 线性探测实现：每次尝试下一个位置
struct linear_probe: public collision_strategy{
    void init();
    int operator()(hash_entry* Table, int table_size, int last_choice) override;
};


// 坏的哈希函数 - 使用所有字符但分布不均匀
struct bad_hashing : public hashing_strategy 
{
    int operator()(char* str, int N) override;
};

// 好的哈希函数 - 使用所有字符且分布均匀  
struct good_hashing : public hashing_strategy 
{
    int operator()(char* str, int N) override;
};

// 双向平方试探冲突处理
struct double_quadratic_probe : public collision_strategy 
{
    int step;
    bool is_add;
    void init() override;
    int operator()(hash_entry* Table, int table_size, int last_choice) override;
};

// 公共溢出区冲突处理
struct common_overflow_area : public collision_strategy 
{
    int overflow_idx;
    void init() override;
    int get_main_size(int table_size);
    int operator()(hash_entry* Table, int table_size, int last_choice) override;
};

// 简单的哈希表类型
struct hashtable{
    hash_entry* Table;                  
    int table_size;                    
    hashing_strategy* my_hashing;       
    collision_strategy* my_collision;   


    hashtable(int size, hashing_strategy* hashing, collision_strategy* collision)
        :table_size(size), my_hashing(hashing), my_collision(collision)
    {
        Table = new hash_entry[table_size];
    }

    bool insert(hash_entry entry){ 
        int N = table_size;
        common_overflow_area* coa = dynamic_cast<common_overflow_area*>(my_collision);
        if (coa != nullptr) N = coa->get_main_size(table_size); 

        int last_choice = (*my_hashing)(entry.my_string, N);
        my_collision->init();
        while(Table[last_choice].my_string != NULL){
            last_choice = (*my_collision)(Table, table_size, last_choice);
        }
        Table[last_choice] = entry;
        return true;
    }

    // 查询键对应的值；返回值：找到则返回对应整数，否则返回 -1
    int query(char* query_string)
    {
        int N = table_size;
        common_overflow_area* coa = dynamic_cast<common_overflow_area*>(my_collision);
        if (coa != nullptr) N = coa->get_main_size(table_size); 

        int last_choice = (*my_hashing)(query_string, N);
        my_collision->init();       
        while(Table[last_choice].my_string != NULL && 
              strcmp(Table[last_choice].my_string, query_string) != 0){
            last_choice = (*my_collision)(Table, table_size, last_choice);
        }
        if(Table[last_choice].my_string == NULL){
            return -1; 
        }
        else {
            return Table[last_choice].my_data;
        }
    }
};
