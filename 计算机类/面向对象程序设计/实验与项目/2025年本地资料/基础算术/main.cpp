#include<iostream>
#include"functions.h"
using namespace std;
int main()
{
    int a{},b{};
    cin>>a>>b;
    int c=custom_sum(a,b);
#ifdef AAAAA
	c= custom_minus(a,b);
#endif
#ifdef BBBBB
    c= custom_product(a,b);
#endif
#ifdef CCCCC
    c= custom_divide(a,b);
#endif
    cout<<c<<endl;
    return 0;
}