#include "manyqueue.h"
#include <cassert>
#include <cstring>
#include <cstdio>
const int maxn = 5000000;
const int maxm = 10000;
int main(){
    int n,m;
    scanf("%d %d",&n, &m); 
    assert(n<=maxn);
    assert(m<=maxm);
    
    QueueManager manager(m);
    char oper[10];
    unsigned int k,x,i;
    while(n--){
        scanf("%s", oper);
        if(strcmp(oper,"push")==0){
            scanf("%u%u",&k,&x);
            manager.push(k,x);
        }else if(strcmp(oper,"pop")==0){
            scanf("%u",&k);
            manager.pop(k);
        }else if(strcmp(oper,"query")==0){
            scanf("%u%u",&k,&i);
            printf("%u\n",manager.query(k,i));
        }else{
            printf("invalid operation:%s",oper);
            return -1;
        }
    }
    return 0;
}