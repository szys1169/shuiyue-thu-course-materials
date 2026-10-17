#include<iostream>
using namespace std;

int main()
{
    int xianyifan[6]={0,0,0,0,0,0};

    for(int i=1;i<=6;i++)
    {
        xianyifan[i]=1;
        int zhenhua=0;
        int A=(xianyifan[1]==0);
        int B=(xianyifan[1]==1||xianyifan[3]==1);
        int C=(A==0&&B==0);
        int F=(xianyifan[6]==1);
        int D=(C==0&&F==0);
        int E=(A+D==2&&B+C+F==0);

        zhenhua=A+B+C+D+E+F;

        if(zhenhua==3)
        {
            char zhuifan='A'-1+i;
            cout<<zhuifan<<endl;
        }
        xianyifan[i]=0;
    }
}