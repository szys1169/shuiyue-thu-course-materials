#pragma once
#include<iostream>

class Factor
{
    int fenzi{};
    int fenmu{};
    int gcd(int a,int b);
    void huajian();
public:
    Factor(int num1=0,int num2=1):fenzi(num1),fenmu(num2)
    {
        huajian();
    }
    friend std::istream& operator>>(std::istream& in, Factor& dst);
    friend std::ostream& operator<<(std::ostream& out, const Factor& src);
    Factor operator+(const Factor& a);
    Factor operator*(const Factor& a);
    Factor operator/(const Factor& a);
    bool operator>(const Factor& a);
    bool operator<(const Factor& a);
    bool operator==(const Factor& a);
};