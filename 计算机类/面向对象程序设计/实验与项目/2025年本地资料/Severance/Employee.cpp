#include<iostream>
#include"_Employee.h"
#include"_Device.h"
#include"Employee.h"
#include"Device.h"
using namespace std;

Employee::Employee(int id):id(id){};
Employee::~Employee(){};

MDRJunior::MDRJunior(int id):Employee(0),id(id){};
Department MDRJunior::getDepartment() const{    return department;}
string MDRJunior::getType() const{return "MDR-Junior";}
void MDRJunior::upgradeLevel(){    level++;}
bool MDRJunior::validate(Device *d){   return d->getAllowedDepartment()==department;}
bool MDRJunior::accessDevice(Device *d){
    if(validate(d)){
        string name=d->getName();
        int length=accessed.size();
        if(name=="BaseLock"){
            cout<<"BaseLock engaged. "<<endl;
            if(length==0){
                accessed.push_back(d);
            }}
        else if(name=="SecurityPanel"){
            if(length>0){
                cout<<"SecurityPanel activated. "<<endl;
                if(length==1){
                    accessed.push_back(d);
                }}
            else{
                cout<<"Dependency not met. ACCESS DENIED. "<<endl;
            }}
        else if(name=="DataTerminal"){
            if(level==0){
                cout<<"No permission. ACCESS DENIED. "<<endl;
            }
            else if(length<2){
                cout<<"Dependency not met. ACCESS DENIED. "<<endl;
            }
            else{
                d->execute();
            }}
        else if(name=="OpticalTool"){
            if(level==1){
                cout<<"OpticalTool adjusted. "<<endl;
            }
            else {
                cout<<"No permission. ACCESS DENIED. "<<endl;
            }}}
    else{
        cout<<"No permission. ACCESS DENIED. "<<endl;
    }
}

MDRSenior::MDRSenior(int id):Employee(0),id(id){};
Department MDRSenior::getDepartment() const{    return department;}
string MDRSenior::getType() const{return "MDR-Senior";}
void MDRSenior::upgradeLevel(){    level++;}
bool MDRSenior::validate(Device *d){   return d->getAllowedDepartment()==department;}
bool MDRSenior::accessDevice(Device *d){
    if(validate(d)){
        string name=d->getName();
        int length=accessed.size();
        if(name=="BaseLock"){
            cout<<"BaseLock engaged. "<<endl;
            if(length==0){
                accessed.push_back(d);
            }}
        else if(name=="SecurityPanel"){
            if(length>0){
                cout<<"SecurityPanel activated. "<<endl;
                if(length==1){
                    accessed.push_back(d);
                }}
            else{
                cout<<"Dependency not met. ACCESS DENIED. "<<endl;
            }}
        else if(name=="DataTerminal"){
            if(level==0){
                cout<<"No permission. ACCESS DENIED. "<<endl;
            }
            else if(length<2){
                cout<<"Dependency not met. ACCESS DENIED. "<<endl;
            }
            else{
                d->execute();
            }}
        else if(name=="OpticalTool"){
            if(level==1){
                cout<<"OpticalTool adjusted. "<<endl;
            }
            else {
                cout<<"No permission. ACCESS DENIED. "<<endl;
            }}}
    else{
        cout<<"No permission. ACCESS DENIED. "<<endl;
    }
}

OnDSenior::OnDSenior(int id):Employee(0),id(id){};
Department OnDSenior::getDepartment() const{    return department;}
string OnDSenior::getType() const{return "O&D-Senior";}
void OnDSenior::upgradeLevel(){    level++;}
bool OnDSenior::validate(Device *d){   return d->getAllowedDepartment()==department;}
bool OnDSenior::accessDevice(Device *d){
    if(validate(d)){
        string name=d->getName();
        int length=accessed.size();
        if(name=="BaseLock"){
            cout<<"BaseLock engaged. "<<endl;
            if(length==0){
                accessed.push_back(d);
            }}
        else if(name=="SecurityPanel"){
            if(length>0){
                cout<<"SecurityPanel activated. "<<endl;
                if(length==1){
                    accessed.push_back(d);
                }}
            else{
                cout<<"Dependency not met. ACCESS DENIED. "<<endl;
            }}
        else if(name=="DataTerminal"){
            if(level==0){
                cout<<"No permission. ACCESS DENIED. "<<endl;
            }
            else if(length<2){
                cout<<"Dependency not met. ACCESS DENIED. "<<endl;
            }
            else{
                d->execute();
            }}
        else if(name=="OpticalTool"){
            if(level==1){
                cout<<"OpticalTool adjusted. "<<endl;
            }
            else {
                cout<<"No permission. ACCESS DENIED. "<<endl;
            }}}
    else{
        cout<<"No permission. ACCESS DENIED. "<<endl;
    }
}

OnDJunior::OnDJunior(int id):Employee(0),id(id){};
Department OnDJunior::getDepartment() const{    return department;}
string OnDJunior::getType() const{return "O&D-Junior";}
void OnDJunior::upgradeLevel(){    level++;}
bool OnDJunior::validate(Device *d){   return d->getAllowedDepartment()==department;}
bool OnDJunior::accessDevice(Device *d){
    if(validate(d)){
        string name=d->getName();
        int length=accessed.size();
        if(name=="BaseLock"){
            cout<<"BaseLock engaged. "<<endl;
            if(length==0){
                accessed.push_back(d);
            }}
        else if(name=="SecurityPanel"){
            if(length>0){
                cout<<"SecurityPanel activated. "<<endl;
                if(length==1){
                    accessed.push_back(d);
                }}
            else{
                cout<<"Dependency not met. ACCESS DENIED. "<<endl;
            }}
        else if(name=="DataTerminal"){
            if(level==0){
                cout<<"No permission. ACCESS DENIED. "<<endl;
            }
            else if(length<2){
                cout<<"Dependency not met. ACCESS DENIED. "<<endl;
            }
            else{
                d->execute();
            }}
        else if(name=="OpticalTool"){
            if(level==1){
                cout<<"OpticalTool adjusted. "<<endl;
            }
            else {
                cout<<"No permission. ACCESS DENIED. "<<endl;
            }}}
    else{
        cout<<"No permission. ACCESS DENIED. "<<endl;
    }
}
