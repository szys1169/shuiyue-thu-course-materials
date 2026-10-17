#include<iostream>
#include<cstdlib>
#include<cstdio>

struct hashnode
{
    unsigned long long key;
    int count=0;
}hashtable[2000003];
const unsigned long long linebase=4099;
const unsigned long long base=32749;


int N,M,n,m,k;
char T[2001][1001];
char P[101][101];//单个P矩阵

unsigned long long linehashT[2001][1001];//行转化为哈希

void insert(unsigned long long key)
{
    int idx=key%2000003;

    while(hashtable[idx].count>0 && hashtable[idx].key!=key)
    {
        idx=(idx+1)%2000003;
    }

    if(hashtable[idx].count==0) // 新的key
    {
        hashtable[idx].key=key;
        hashtable[idx].count=1;
    }
    else // key已存在
    {
        hashtable[idx].count++;
    }
}

//查询P的哈希在哈希表中的出现次数
int query(unsigned long long key)
{
    int idx=key%2000003;

    while(hashtable[idx].count>0 && hashtable[idx].key!=key)
    {
        idx=(idx+1)%2000003;
    }

    return hashtable[idx].key==key ? hashtable[idx].count : 0;
}

//给出T矩阵的哈希表
void computeThash()
{
    // 预处理幂次
    unsigned long long pow1[101], pow2[101];
    pow1[0] = pow2[0] = 1;
    for (int i = 1; i <= n; i++) 
    {
        pow1[i] = pow1[i-1] * linebase;
    }
    for (int i = 1; i <= m; i++) 
    {
        pow2[i] = pow2[i-1] * base;
    }

    for(int i=0;i<M;i++)
    {
        unsigned long long sum=0;  
        for(int j=0;j<n;j++)
        {
            sum=sum*linebase+T[i][j];
        }
        linehashT[i][0]=sum;

        for(int j=1;j<=N-n;j++)
        {
            sum=sum*linebase-T[i][j-1]*pow1[n]+T[i][j+n-1];
            linehashT[i][j] = sum;
        }
    }

    for (int col = 0; col + n <= N; col++) 
    {
        unsigned long long sum = 0;  
        for (int row = 0; row < m; row++) 
        {
            sum = sum * base + linehashT[row][col];
        }
        insert(sum);
        
        for (int row = 1; row + m <= M; row++)
        {
            sum = sum * base - linehashT[row-1][col] * pow2[m] + linehashT[row+m-1][col];
            insert(sum);
        }
    }
}

//计算当前P的哈希
unsigned long long computePhash()
{
    unsigned long long linehash[101];

    for(int i=0;i<m;i++)
    {
        unsigned long long sum=0;  
        for(int j=0;j<n;j++)
        {
            sum=sum*linebase+P[i][j];
        }
        linehash[i]=sum;
    }

    unsigned long long sum=0;  
    for(int i=0;i<m;i++)
    {
        sum=sum*base+linehash[i];
    }
    return sum;
}

int main()
{
    scanf("%d%d%d%d%d",&M,&N,&m,&n,&k);
    
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            scanf(" %c",&T[i][j]);
        }
    }

    computeThash();

    for(int p=0;p<k;p++)
    {
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                scanf(" %c",&P[i][j]);
            }
        }

        unsigned long long Phash=computePhash();
        printf("%d\n", query(Phash));
    }

    return 0;
}