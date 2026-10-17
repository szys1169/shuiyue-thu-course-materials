#include<iostream>
#include<cmath>
using namespace std;

void qiugeng(int a,int b,int c)
{
    float x1,x2;
    x1=(-b+sqrt(b^2+4*a*c))/2/a;
    x2=(-b-sqrt(b^2+4*a*c))/2/a;
    if(x1<x2)
    {
        cout<<x1<<" "<<x2;
    }
    else 
    {
        cout<<x2<<" "<<x1;
    }
}

int main()
{
    int a,b,c;
    cin>>a>>b>>c;
    qiugeng(a,b,c);
}