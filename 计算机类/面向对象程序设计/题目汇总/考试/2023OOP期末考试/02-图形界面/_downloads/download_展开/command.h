#pragma once
#include "window.h"
#include <iostream>
#include <memory>
#include <list>
using namespace std;

class ClearAll {
    // TODO
public:
    // TODO
    ClearAll(list<shared_ptr<Checkbox>> checkbox);
    void operator()();
};

class SelectAll {
    // ...
public:
    // TODO
    SelectAll(list<shared_ptr<Checkbox>> checkbox);
    void operator()();
};

class Submit {
    // ...
public:
    // TODO
    Submit(list<shared_ptr<Checkbox>> checkbox);
    void operator()();
};