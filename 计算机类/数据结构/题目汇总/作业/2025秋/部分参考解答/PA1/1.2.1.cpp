#include<cstdio>
#include<cstdlib>
#include<cstring>

long long* sum(long long* c1,long long* c2,int count,int& size)
{
    long long* sum=new long long[size];
    sum[0]=0;
    for(int i=0;i<count;i++)
    {
        long long* newSum=new long long[2*size];
        for(int j=0;j<size;j++)
        {
            newSum[2*j]=sum[j]+c1[i];
            newSum[2*j+1]=sum[j]+c2[i];
        }
        delete[] sum; 
        sum=newSum;
        size*=2;
    }
    return sum;
}

int compare(const void* a, const void* b) 
{
    long long c = *(const long long*)a;
    long long d = *(const long long*)b;
    
    if (c < d) return -1;  
    if (c > d) return 1;   
    return 0;                   
}//此处和qsort的用法来源于ai

int check(long long* sum,int size,long long maxValue)
{
    int left=0;
    int right=size;
    while(left<right)
    {
        int mid=(left+right)/2;
        if(sum[mid]>maxValue)
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
    long long n,P;
    std::scanf("%lld%lld",&n, &P);

    long long c1[n];
    long long c2[n];
    for(int i=0;i<n;i++)
    {
        std::scanf("%lld%lld",&c1[i], &c2[i]);
    }

    int leftCount=n/2;
    int rightCount=n-leftCount;

    int leftSize=1;
    int rightSize=1;
    long long* leftSum=sum(c1,c2,leftCount,leftSize);
    long long* rightSum=sum(c1+leftCount,c2+leftCount,rightCount,rightSize);

    qsort(rightSum,rightSize,sizeof(long long),compare);//用法查询自ai

    long long total=0;
    for(int i=0;i<leftSize;i++)
    {
        total+=check(rightSum,rightSize,P-leftSum[i]);
    }

    std::printf("%lld",total);

    return 0;
}