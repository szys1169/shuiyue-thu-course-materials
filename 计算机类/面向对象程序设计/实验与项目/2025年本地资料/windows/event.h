#pragma once
#include <functional>
#include<vector>
using namespace std;

class Click {
private:   
    // TODO
public:
    function<void()> functions;
    // TODO
    Click():functions(){}
    // TODO
    void setClickCommand(std::function<void()> f)
    {
        functions=f;
    }
    // TODO
    virtual void click()
    {
        if(functions)functions();
    }
};

class DoubleClick {
private:
    
    // TODO
public:
    function<void()> doublefunctions;
    // TODO
    DoubleClick():doublefunctions(){}
    // TODO
    void setDoubleClickCommand(std::function<void()> f)
    {
        doublefunctions=f;
    }
    // TODO
    virtual void doubleClick()
    {
        if(doublefunctions)doublefunctions();
    }
};