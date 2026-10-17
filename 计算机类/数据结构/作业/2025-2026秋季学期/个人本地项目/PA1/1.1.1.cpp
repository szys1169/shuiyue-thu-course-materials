#include<string>
#include<iostream>
#include<cstdio>
#include <cstdlib>

int main()
{
    int N,M,K; 
    std::string A,B;
    std::cin>>N>>M>>K;
    std::cin>>A>>B;
    int ans=0;
    int dp[202]{};
    int memory[202]{};
    for(int i=0;i<=K;i++)
    {
        dp[i+101]=i;
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=-K;j<=K;j++)
        {
            if(i<=K)memory[101-i]=i;
            if(i+j<1)
            {
                continue;
            }
            if(j==K||j==-K)
            {
                memory[101+K]=K+1;
            }
            else if(A[i-1]==B[i+j-1])
            {
                memory[101+j]=dp[101+j];
            }
            else
            {
                memory[101+j]=std::min(dp[102+j],memory[100+j])+1;
            }
        }
        for(int j=-K;j<=K;j++)
        {
            dp[101+j]=memory[101+j];
        }
    }
    ans=dp[M-N+101];
    if( ans >K ||M-N>100||N-M>100)ans=-1;
    std::cout<<ans<<std::endl;
    return 0;
}