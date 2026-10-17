#include<cstdio>
#include<cstdlib>
#include<iostream>

int compare(const void* a, const void* b) 
{
    long long c = *(const long long*)a;
    long long d = *(const long long*)b;
    
    if (c < d) return -1;  
    if (c > d) return 1;   
    return 0;                   
}

int check(long long* x,long long* y,int xx,int yy,int n)
{
    int left=0;
    int right=n;
    while(left<right)
    {
        int mid=(left+right)/2;
        if(yy*x[mid]+xx*y[mid]<y[mid]*x[mid])
        {
            right=mid;
        }
        else 
        {
            left=mid+1;
        }
    } 
    return left;  
}

int main()
{
    int n;
    long long x[200000]{};
    long long y[200000]{};
    int m;
    long long xx[200000]{};
    long long yy[200000]{};
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%lld",&x[i]);
    }
    for(int i=0;i<n;i++)
    {
        scanf("%lld",&y[i]);
    }
    scanf("%d",&m);
    for(int i=0;i<m;i++)
    {
        scanf("%lld%lld",&xx[i],&yy[i]);
    }
    qsort(x,n,sizeof(long long),compare);
    qsort(y,n,sizeof(long long),compare);
    for(int i=0;i<m;i++)
    {
        int xnumber=check(x,y,xx[i],yy[i],n);
        int ynumber=check(x,y,xx[i],yy[i],n);
        int result=std::max(xnumber,ynumber);
        printf("%d\n",result);
    }
    return 0;
}