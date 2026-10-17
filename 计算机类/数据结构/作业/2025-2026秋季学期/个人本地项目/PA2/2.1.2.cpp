#include<cstdio>
#include<cstdlib>

//二分查找
int check(int* result, int n, long long val) 
{
    int left=0;
    int right=n;
    while (left < right) 
    {
        int mid = left + (right - left) / 2;
        if (result[mid] < val) 
        {
            left = mid + 1;
        } 
        else 
        {
            right = mid;
        }
    }
    return left;
}

// qsort所需的比较函数
int compare(const void* a, const void* b) 
{
    int val1 = *(const int*)a;
    int val2 = *(const int*)b;
    if (val1 < val2) return -1;
    if (val1 > val2) return 1;
    return 0;
}

int main()
{
    int n;
    scanf("%d",&n);
    int *x=new int[n];
    long long *m=new long long[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&x[i]);
    }
    for(int i=0;i<n;i++)
    {
        scanf("%lld",&m[i]);
    }

    int *data=new int[n];//辅助数列，存储递减索引
    int *result=new int[n];//存储结果
    int first=0;int end=0;
    result[0]=0;data[0]=0;

    for(int i=1;i<n;i++)
    {
        long long left=i-m[i];
        if(left<0)left=0;
        int right=i-1;//边界

        while(first<end && x[right]>x[data[end-1]])end--;//剔除比当前数据小的元素
        data[end]=right;
        end+=1;
        
        while(first<end && data[first]<left)first++;//去除边界外的元素

        result[i]=x[data[first]];
    }

    qsort(result, n, sizeof(int), compare);

    int T;
    scanf("%d",&T);
    long long p,q;
    int countlow=0;
    int countmid=0;
    for(int i=1;i<=T;i++)
    {
        scanf("%lld%lld",&p,&q);
        countlow=check(result,n,p);
        countmid=check(result,n,q)-countlow;
        printf("%d %d\n",countlow,countmid);
    }
    return 0;
}