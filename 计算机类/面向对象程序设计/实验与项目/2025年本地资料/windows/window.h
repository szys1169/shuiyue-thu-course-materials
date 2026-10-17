#pragma once
#include <memory>
#include <list>
#include<stack>
#include "event.h"

using namespace std;

class Window;

class Widget 
{
    Window* _parent;
public:
    string _name;
    Widget(string name) :_name(name), _parent(nullptr) {}
    string getName() const { return _name; }
    Window* getParent() const { return _parent; }
    void setParent(Window * parent) {_parent = parent;}
    virtual ~Widget() {}
};

class Button :public Widget, public Click, public DoubleClick {
public:
    Button(string name) :Widget(name) {}
};

class Window {

private:
    list<shared_ptr<Widget>> Widgets;
    stack<function<void()>> undojilu;
    // TODO

public:
    // TODO
    shared_ptr<Widget> getPointerByName(string name)
    {
        for(auto it:Widgets)
        {
            if(it->getName()==name)
            {
                return it;
            }
        }
        return nullptr;
    }
    // TODO
    Widget& getElementByName(string name)
    {
        for(auto it:Widgets)
        {
            if(it->getName()==name)
            {
                return *it; 
            }
        }
    }
    // TODO
    bool addElement(shared_ptr<Widget> w)
    {
        for(auto it:Widgets)
        {
            if(it->getName()==w->getName())
            {
                return false;
            }
        }
        Widgets.push_back(w);
        w->setParent(this);
        return true;
    }
    // TODO
    void recordundo(std::function<void()> action)
    {
        undojilu.push(action);
    }
    bool undo()
    {
        if(undojilu.empty())
        {
            return false;
        }
        undojilu.top()();
        undojilu.pop();
        return true;
    }
};

class Checkbox :public Widget, public Click 
{
    Window* window;
    public:
    bool panduan=0;
    Checkbox(string _name):Widget(_name),panduan(0)
    {
        window=getParent();
        setClickCommand([this]() {
            bool prev = panduan;
            panduan = !panduan;
            if (window) { 
                window->recordundo([this, prev]() { panduan = prev; });
            }
        });
    }
    void setParent(Window *parent) { Widget::setParent(parent);window = parent;}
};