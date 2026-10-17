#include"Fraction.h"
#include<iostream>

int Fraction::gcd(int a,int b)
{
    if(a<0)a=-a;
    if(b<0)b=-b;
    while(b!=0)
    {
        int tmp=b;
        b=a%b;
        a=tmp;
    }
    return a;
}

void Fraction::huajian()
{
    if(zi==0&&mu==0)
    {
        return;
    }
    if(zi==0)
    {
        mu=1;
        return;
    }
    int linshi=gcd(zi,mu);
    zi=zi/linshi;
    mu=mu/linshi;
}

std::ostream& operator<<(std::ostream& out, const Fraction& src)
{
    int zi=src.zi;
    int mu=src.mu;
    if(src.mu<0)
    {
        zi=-src.zi;
        mu=-src.mu;
    }
    if(zi%mu==0)out<<zi/mu;
    else out<<zi<<"/"<<mu;
    return out;
}

Fraction Fraction::operator+(const Fraction& a)
{
    Fraction b=Fraction(zi*a.mu+mu*a.zi,mu*a.mu);
    b.huajian();
    return b;
}

Fraction Fraction::operator+(const int& a)
{
    Fraction b=Fraction(zi+a*mu,mu);
    b.huajian();
    return b;
}

Fraction Fraction::operator-(const Fraction& a)
{
    Fraction b=Fraction(zi*a.mu-mu*a.zi,mu*a.mu);
    b.huajian();
    return b;
}

Fraction Fraction::operator-(const int& a)
{
    Fraction b=Fraction(zi-a*mu,mu);
    b.huajian();
    return b;
}

Fraction Fraction::operator*(const Fraction& a)
{
    Fraction b=Fraction(zi*a.zi,mu*a.mu);
    b.huajian();
    return b;
}

Fraction Fraction::operator*(const int& a)
{
    Fraction b=Fraction(zi*a,mu);
    b.huajian();
    return b;
}

Fraction Fraction::operator/(const Fraction& a)
{
    Fraction b=Fraction(zi*a.mu,mu*a.zi);
    b.huajian();
    return b;
}

Fraction Fraction::operator=(const int &a)
{
    Fraction b(a);
    this->zi=b.zi;
    this->mu=b.mu;
    return b;
}