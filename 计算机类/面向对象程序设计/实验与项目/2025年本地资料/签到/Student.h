#pragma once
#include<iostream>
#include <string>
using namespace std;

class Student
{
    string name{};
    public:
    int times=0;
    int absenttime=0;
    Student(string a):name(a){};
    string getName(){return name;};
    int getPresentTimes(){return times;};
    int getAbsentTimes(){return absenttime;};
};