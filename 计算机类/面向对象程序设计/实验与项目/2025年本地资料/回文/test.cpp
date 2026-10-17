#include<iostream>

using namespace std;

int main()
{
    char* str =new char[3];

    for(int i=0;i<3;i++)
    {
        str[i]='a'+i;
    }

    cout<< str << endl;

    int* a= new int[5];
    for(int i=0;i<5;i++)
    {
        a[i]=i;
    }

    cout<<a<<endl;

    return 0;
}