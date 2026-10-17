#include <iostream>
#include <cstdlib>

using namespace std;

int n, m;

int cmp_int(const void* a, const void* b){
    if(*(long long*)a < *(long long*)b){
        return 1;
    }else{
        return -1;
    }
}

int main(){
    scanf("%d", &n);
    long long arrx[n],arry[n];
    for(int i=0;i<n;i++){
        scanf("%lld", arrx+i);
    }
    for(int i=0;i<n;i++){
        scanf("%lld", arry+i);
    }
    scanf("%d", &m);
    qsort(arrx, n, 8, cmp_int);
    qsort(arry, n, 8, cmp_int);
    for(int i=0;i<m;i++){
        long long x, y;
        scanf("%lld %lld", &x, &y);
        int lo=0, hi=n;
        //保持[0,lo)>=e>[hi,n)
        while (lo<hi){
            int m=(lo+hi)/2;
            if(x*arry[m]+y*arrx[m]<arrx[m]*arry[m]) hi=m;
            else lo=m+1;
        }
        printf("%d\n", lo);
        
    }
}