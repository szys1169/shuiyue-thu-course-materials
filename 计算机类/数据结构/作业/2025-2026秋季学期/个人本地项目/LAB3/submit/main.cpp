#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <time.h>
#include "hashtable.h"



int main()
{
    int type;                   
    char buffer[1000]; int data; 
    clock_t start, end;
    double cpu_time_used;
    //hashtable table(10000, new naive_hashing(), new linear_probe());

    int hash_choice=0;
    int collision_choice=0;
    scanf("%d %d", &hash_choice, &collision_choice);

    hashing_strategy* hashing = nullptr;
    collision_strategy* collision = nullptr;

    switch (hash_choice)
    {
        case 1: hashing = new bad_hashing(); break;
        case 2: hashing = new good_hashing(); break;
    }

    switch (collision_choice)
    {
        case 1: collision = new linear_probe(); break;
        case 2: collision = new double_quadratic_probe(); break;
        case 3: collision = new common_overflow_area(); break;
    }

    hashtable table(10000, hashing, collision);

    start = clock();  // 记录开始时间
    

    while(true)
    {
        double current_used = ((double)(clock() - start)) / CLOCKS_PER_SEC;
        if (current_used > 100.0) {
            printf(">60\n");  
            return 0;         
        }

        // 读取操作类型
        if(scanf("%d", &type) != 1) break; 
        if(type == 0)
        {
            scanf("%s", buffer);
            scanf("%d", &data);
            table.insert(hash_entry(buffer, data));
        } 
        else if(type == 1)
        {
            scanf("%s", buffer);
            printf("%d\n", table.query(buffer));
        } 
        else break;
    }

    end = clock();    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    //std::cout << "time: " << cpu_time_used << " s" << std::endl;

    
    return 0;
}