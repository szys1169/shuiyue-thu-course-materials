#include"Factor.h"
#include<iostream>

int Factor::gcd(int a,int b)
{
    while(b!=0)
    {
        int tmp=b;
        b=a%b;
        a=tmp;
    }
    return a;
}

void Factor::huajian()
{
    if(fenzi==0&&fenmu==0)
    {
        return;
    }
    if(fenzi==0)
    {
        fenmu=1;
        return;
    }
    int linshi=gcd(fenzi,fenmu);
    fenzi=fenzi/linshi;
    fenmu=fenmu/linshi;
}

std::istream& operator>>(std::istream& in, Factor& dst)
{
    char linshi;
    in>>dst.fenzi>>linshi>>dst.fenmu;
    dst.huajian();
    return in;
}

std::ostream& operator<<(std::ostream& out, const Factor& src)
{
    if(src.fenmu==0)
    {
        out<<"nan";
    }
    else 
    {
        out<<src.fenzi<<"/"<<src.fenmu;
    }
    return out;
}

Factor Factor::operator+(const Factor& a)
{
    Factor b=Factor(fenzi*a.fenmu+fenmu*a.fenzi,fenmu*a.fenmu);
    b.huajian();
    return b;
}

Factor Factor::operator*(const Factor& a)
{
    Factor b=Factor(fenzi*a.fenzi,fenmu*a.fenmu);
    b.huajian();
    return b;
}

Factor Factor::operator/(const Factor& a)
{
    Factor b=Factor(fenzi*a.fenmu,fenmu*a.fenzi);
    b.huajian();
    return b;
}

bool Factor::operator>(const Factor& a)
{
    if(fenzi*a.fenmu-fenmu*a.fenzi>0)return true;
    else return false;
}

bool Factor::operator<(const Factor& a)
{
    if(fenzi*a.fenmu-fenmu*a.fenzi<0)return true;
    else return false;
}

bool Factor::operator==(const Factor& a)
{
    if(fenzi*a.fenmu-fenmu*a.fenzi==0)return true;
    else return false;
}