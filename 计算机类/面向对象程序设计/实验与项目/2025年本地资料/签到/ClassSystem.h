#pragma once
#include<iostream>
#include <string>
#include<vector>
#include"Student.h"
using namespace std;

class ClassSystem
{
    vector<Student> c;
    int counnt=0;
    public:
    void addClassNumber()
    {
       counnt++;
    };
    void addStudent(Student stu)
    {
        c.push_back(stu);
    };
    void signIn(string name)
    {
        for(int i=0;i<c.size();i++)
        {
            if(name==c[i].getName())
            {
                c[i].times++;
                break;
            }
        }
    };
    Student getStudentById(int i)
    {
        c[i].absenttime=counnt-c[i].times;
        return c[i];
    };
    Student getStudentByName(string name)
    {
        for(int i=0;i<c.size();i++)
        {
            c[i].absenttime=counnt-c[i].times;
            if(name==c[i].getName())
            {
                return c[i];
            }
        }
    };
};