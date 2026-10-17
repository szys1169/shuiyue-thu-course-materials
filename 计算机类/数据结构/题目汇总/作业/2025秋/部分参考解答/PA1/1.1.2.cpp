#include<cstdio>
#include <cstdlib>

int main()
{
    long long m, n;
    int place=0;
    std::scanf("%lld%lld",&n, &m);

    int* people = (int*)malloc(n * sizeof(int));
    int* leftpeople = (int*)malloc(n * sizeof(int));
    int* rightpeople = (int*)malloc(n * sizeof(int));

    for(int i=0;i<n;i++)
    {
        std::scanf("%lld",&people[i]);
    }
    
    leftpeople[0]=0;
    rightpeople[0]=0;

    for(int i=1;i<n;i++)
    {
        int move=m%i;
        place=i-1;
        for(int j=1;j<=move;j++) 
        {
            place=rightpeople[place];
        }

        rightpeople[i]=place;
        leftpeople[i]=leftpeople[place];
        leftpeople[place]=i;
        rightpeople[leftpeople[i]]=i;//更新位置
    }

    for(int i=1;i<=n;i++)
    {
        place=leftpeople[place];
        std::printf("%d%s",people[place]," ");
    }

    return 0;
}