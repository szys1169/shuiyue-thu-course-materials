#pragma once
#include <memory>
#include <list>
#include "event.h"

using namespace std;

class Window;

class Widget {
    string _name;
    Window* _parent;
public:
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

class Checkbox :public Widget, public Click {
    // TODO
};

class Window {

private:
    list<shared_ptr<Widget>> Widgets;
    // TODO

public:
    // TODO
    shared_ptr<Widget> getPointerByName(string name);
    // TODO
    Widget& getElementByName(string name);
    // TODO
    bool addElement(shared_ptr<Widget> w);
    // TODO
    bool undo();
};
