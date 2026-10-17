#include<iostream>
#include"_Device.h"
#include"Device.h"
using namespace std;

bool BaseLock::isUnlocked(const std::vector<Device *> &accessed)
{
    return true;
}
void BaseLock::execute(){};
std::string BaseLock::getName() const
{
    return "BaseLock";
}
Department BaseLock::getAllowedDepartment() const
{
    return MACRODATA_REFINEMENT;
}

bool SecurityPanel::isUnlocked(const std::vector<Device *> &accessed)
{
    return true;
}
void SecurityPanel::execute(){};
std::string SecurityPanel::getName() const
{
    return "SecurityPanel";
}
Department SecurityPanel::getAllowedDepartment() const
{
    return MACRODATA_REFINEMENT;
}

DataTerminal::DataTerminal(int rl):rongliang(rl){};
bool DataTerminal::isUnlocked(const std::vector<Device *> &accessed)
{
    return true;
}
void DataTerminal::execute()
{
    cout<<"Processed "<<rongliang<<"TB data."<<endl;
};
std::string DataTerminal::getName() const
{
    return "DataTerminal";
}
Department DataTerminal::getAllowedDepartment() const
{
    return MACRODATA_REFINEMENT;
}

bool OpticalTool::isUnlocked(const std::vector<Device *> &accessed)
{
    return true;
}
void OpticalTool::execute(){};
std::string OpticalTool::getName() const
{
    return "OpticalTool";
}
Department OpticalTool::getAllowedDepartment() const
{
    return OPTICS_AND_DESIGN;
}
