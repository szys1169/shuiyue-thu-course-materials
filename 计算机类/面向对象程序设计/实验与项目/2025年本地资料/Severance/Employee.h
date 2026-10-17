#pragma once
#include<iostream>
#include"_Employee.h"
#include"_Device.h"
#include"Device.h"
using namespace std;


class MDRSenior:public Employee,public SecurityProfile
{
public:
    int id;
    MDRSenior(int id);
    int level=1;
    Department department=MACRODATA_REFINEMENT;
    std::vector<Device *> accessed;
    bool validate(Device *d);
    void upgradeLevel();
    bool accessDevice(Device *d);
    std::string getType() const;
    Department getDepartment() const;
    MDRSenior *clone()
    {
        return this;
    }
    MDRSenior *promote()
    {
        return this;
    }
    ~MDRSenior(){}
};

class MDRJunior:public Employee,public SecurityProfile
{
public:
    int id;
    MDRJunior(int id);
    int level=0;
    Department department=MACRODATA_REFINEMENT;
    std::vector<Device *> accessed;
    bool validate(Device *d);
    void upgradeLevel();
    bool accessDevice(Device *d);
    std::string getType() const;
    Department getDepartment() const;
    MDRJunior *clone()
    {
        return this;
    }
    MDRSenior *promote()
    {
        MDRSenior *xin=new MDRSenior(id);
        xin->level=1;
        xin->accessed=this->accessed;
        return xin;
    }
    ~MDRJunior(){}
};

class OnDSenior:public Employee,public SecurityProfile
{
public:
    int id;
    OnDSenior(int id);
    int level=1;
    Department department=OPTICS_AND_DESIGN;
    std::vector<Device *> accessed;
    bool validate(Device *d);
    void upgradeLevel();
    bool accessDevice(Device *d);
    std::string getType() const;
    Department getDepartment() const;
    OnDSenior *clone()
    {
        return this;
    }
    OnDSenior *promote()
    {
        return this;
    }
    ~OnDSenior(){}
};

class OnDJunior:public Employee,public SecurityProfile
{
public:
    int id;
    OnDJunior(int id);
    int level=0;
    Department department=OPTICS_AND_DESIGN;
    std::vector<Device *> accessed;
    bool validate(Device *d);
    void upgradeLevel();
    bool accessDevice(Device *d);
    std::string getType() const;
    Department getDepartment() const;
    OnDJunior *clone()
    {
        return this;
    }
    OnDSenior *promote()
    {
        OnDSenior *xin =new OnDSenior(id);
        xin->level=1;
        xin->accessed=this->accessed;
        return xin;
    }
    ~OnDJunior(){}
};