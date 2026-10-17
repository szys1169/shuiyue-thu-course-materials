#include <iostream>
using namespace std;
class PyObject{
private:
    void *lei;
public:
    template<class T>operator T() const{ return *(T*)lei; }
    PyObject& operator=(int i){lei=static_cast<void*>(&i);cout<<"PyObject got a value"<<endl;return *this;};
    PyObject& operator=(char i){lei=static_cast<void*>(&i);cout<<"PyObject got a value"<<endl;return *this;};
    PyObject& operator=(double i){lei=static_cast<void*>(&i);cout<<"PyObject got a value"<<endl;return *this;};
    template<class T>PyObject& operator=(T& i){lei=static_cast<void*>(&i);cout<<"PyObject got a value"<<endl<<"Borrowing"<<endl;return *this;}
};
