#pragma once
#include <iostream>
using namespace std;
class PyObject{
private:
    int zhengshu=0;char zifu=' ';double xiaoshu=0.0;
    void *lei;
public:
    operator int() const{return zhengshu;};operator char() const{return zifu;};operator double() const{return xiaoshu;};
    PyObject& operator=(int i){zhengshu=i;cout<<"PyObject got a value"<<endl;return *this;};
    PyObject& operator=(char i){zifu=i;cout<<"PyObject got a value"<<endl;return *this;};
    PyObject& operator=(double i){xiaoshu=i;cout<<"PyObject got a value"<<endl;return *this;};
    
    template<class T>operator T() const{T*b=static_cast<T*>(lei);return *b;}

    //template<class T>operator T&() {T*b=static_cast<T*>(lei);return *b;}
    template<class T>PyObject& operator=(T& i){lei=static_cast<void*>(&i);cout<<"PyObject got a value"<<endl<<"Borrowing"<<endl;return *this;}
    //template<class T>PyObject& operator=(T&& i){lei=&i;cout<<"PyObject got a value"<<endl<<"Owning"<<endl;return *this;}
    //template<class T>T& operator=(PyObject& i){T*b=static_cast<T*>(lei);return *b;}
    //template<class T>T& operator=(PyObject&& i){T*b=static_cast<T*>(lei);return *b;}
    
};
