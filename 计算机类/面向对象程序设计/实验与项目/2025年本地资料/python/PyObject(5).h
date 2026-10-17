#pragma once

#include <iostream>
#include <typeinfo>
#include <memory>
#include <utility>
#include <type_traits>
#include <string>
#include <cstring>
#include<algorithm>
using namespace std;

class PyObject{
shared_ptr<void> val=nullptr;
bool owning=0;
public:
PyObject &operator=(int val)
{
    cout << "PyObject got a value"<<endl;
    owning=false;
    this->val=make_shared<int>(val);
    return *this;
};
PyObject &operator=(double val)
{
    cout << "PyObject got a value"<<endl;
    owning=false;
    this->val=make_shared<double>(val);
    return *this;
};
PyObject &operator=(char val)
{
    cout << "PyObject got a value"<<endl;
    owning=false;
    this->val=make_shared<char>(val);
    return *this;
};
template< typename T >
 PyObject& operator=(T& value)
    {
        cout << "PyObject got a value" << endl;
        owning = false;
        using DecayedT = typename std::remove_cv<T>::type;
        val= shared_ptr<void>(addressof(const_cast<DecayedT&>(value)), [](void*){});
        cout << "Borrowing" << endl;
        return *this;
    };
    
    // Template assignment operator for rvalues (owning)
    template<typename T>
    PyObject& operator=(T&& value)
    {
        cout << "PyObject got a value" << endl;
        owning = true;
        using DecayedT = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
        val= make_shared<DecayedT>(std::forward<T>(value));
        cout << "Owning" << endl;
        return *this;
    };
     operator int() const
    {
        return *static_pointer_cast<int>(val);
    }
    operator double() const
    {
        return *static_pointer_cast<double>(val);
    }
    operator char() const
    {
        return *static_pointer_cast<char>(val);
    }
    template<typename T> 
    operator T() const
    {
        auto ptr = std::static_pointer_cast<T>(val);
        return *ptr; 
    }
    template<typename T> 
    operator T&()
    {
        return *static_pointer_cast<T>(val);
    }
};

    