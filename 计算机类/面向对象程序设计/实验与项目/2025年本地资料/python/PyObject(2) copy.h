#pragma once
#include <iostream>
#include<typeinfo>
#include<memory>
#include <utility>
#include <type_traits>
using namespace std;

class PyObject
{
    shared_ptr<void> data;
    bool owns=false;
    public:
    void clear()
    {
        data.reset();
        owns=false;
    }
    PyObject():data(nullptr){};
    ~PyObject(){clear();};
    PyObject& operator=(int val)
    {
        cout << "PyObject got a value"<<endl;
        clear();
        owns=false;
        data=make_shared<int>(val);
        return *this;
    }
    PyObject& operator=(double val)
    {
        cout << "PyObject got a value"<<endl;
        clear();
        owns=false;
        data=make_shared<double>(val);
        return *this;
    }
    PyObject& operator=(char val)
    {
        cout << "PyObject got a value"<<endl;
        clear();
        owns=false;
        data=make_shared<char>(val);
        return *this;
    }
    template<typename T> 
    PyObject& operator=(T& val)
    {
        cout << "PyObject got a value"<<endl;
        clear();
        owns=false;
        data=shared_ptr<void>(addressof(val), [](void*){}); 
        cout<<"Borrowing"<<endl;
        return *this;
    }
    template<typename T> 
    PyObject& operator=(T&& val)
    {
        cout << "PyObject got a value"<<endl;
        clear();
        owns=true;
        data=make_shared<T>(move(val));
        cout<<"Owning"<<endl;
        return *this;
    }
    PyObject& operator=(PyObject& other)
    {
        cout << "PyObject got a value"<<endl;
        clear();
        if(other.owns)
        {
            owns=true;
            data =other.data;
            cout<<"Owning"<<endl;
        }
        else
        {
            data=other.data;
            owns=false;
            cout<<"Borrowing"<<endl;
        }
        return *this;
    }
    PyObject& operator=(PyObject&& other)
    {
        cout << "PyObject got a value"<<endl;
        clear();
        if(other.owns)
        {
            data=move(other.data);
            cout<<"Owning"<<endl;
            owns=true;
        }
        else
        {
            data=move(other.data);
            cout<<"Borrowing"<<endl;
            owns=false;
        }
        other.data=nullptr;
        other.owns=false;
        return *this;
    }
    PyObject& operator=(PyObject* other)
    {
        cout << "PyObject got a value"<<endl;
        clear();
        owns=false;
        data=other->data;
        cout<<"Borrowing"<<endl;
        return *this;
    }
    operator int() const
    {
        return *static_pointer_cast<int>(data);
    }
    operator double() const
    {
        return *static_pointer_cast<double>(data);
    }
    operator char() const
    {
        return *static_pointer_cast<char>(data);
    }
    template<typename T> 
    operator T() const
    {
        auto ptr = std::static_pointer_cast<T>(data);
        return *ptr; 
    }
    template<typename T> 
    operator T&()
    {
        return *static_pointer_cast<T>(data);
    }
};