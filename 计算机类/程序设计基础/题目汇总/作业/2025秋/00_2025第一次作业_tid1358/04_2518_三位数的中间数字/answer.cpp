#include<iostream>
using namespace std;

int main()
{
    int A,B;
    
    cin>>A>>B;

    int liangweishu=A%100;
    int C=liangweishu/10;
    if(C==B)
    {
        cout<<"YES";
    }
    else
    {
        cout<<"NO";
    }

}