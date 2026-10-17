#pragma once
#include<iostream>
#include"_Device.h"
using namespace std;

class BaseLock:public Device
{
public:
    BaseLock(){};
    ~BaseLock(){};
    bool isUnlocked(const std::vector<Device *> &accessed);
    void execute();
    std::string getName() const;
    Department getAllowedDepartment() const;
};

class SecurityPanel:public Device
{
public:
    SecurityPanel(){};
    bool isUnlocked(const std::vector<Device *> &accessed);
    void execute();
    std::string getName() const;
    Department getAllowedDepartment() const;
};

class DataTerminal:public Device
{
public:
    int rongliang;
    ~DataTerminal(){};
    DataTerminal(int rl);
    bool isUnlocked(const std::vector<Device *> &accessed);
    void execute();
    std::string getName() const;
    Department getAllowedDepartment() const;
};

class OpticalTool:public Device
{
public:
    OpticalTool(){};
    ~OpticalTool(){};
    bool isUnlocked(const std::vector<Device *> &accessed);
    void execute();
    std::string getName() const;
    Department getAllowedDepartment() const;
};