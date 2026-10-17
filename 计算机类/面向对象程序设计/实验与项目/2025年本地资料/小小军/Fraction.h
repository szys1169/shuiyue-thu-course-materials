#pragma once
#include<iostream>
using namespace std;

class Fraction
{
    long long int zi;
    long long int mu;
    void huajian();
    int gcd(int a,int b);
    public:
    Fraction():zi(0),mu(1){}
    Fraction(int n):zi(n),mu(1){huajian();};
    Fraction(int num1,int num2):zi(num1),mu(num2){huajian();}
    friend std::ostream& operator<<(std::ostream& out, const Fraction& src);
    Fraction operator+(const Fraction& a);
    Fraction operator+(const int& a);
    Fraction operator-(const Fraction& a);
    Fraction operator-(const int& a);
    Fraction operator*(const Fraction& a);
    Fraction operator*(const int& a);
    Fraction operator/(const Fraction& a);
    Fraction operator=(const int& a);
};