#pragma once
#include "window.h"
#include <iostream>
#include <memory>
#include <list>
using namespace std;

class ClearAll {
    // TODO
    list<shared_ptr<Checkbox>> ccheckbox;
    Window* window;
public:
    // TODO
    ClearAll(list<shared_ptr<Checkbox>> checkbox):ccheckbox(checkbox)
    {
        if(!ccheckbox.empty())
        {
            window=ccheckbox.front()->getParent();
        }
        else window=nullptr;
    }
    void operator()()
    {
         vector<bool> local_jilu; 
            for (auto& checkbox : ccheckbox) {
           local_jilu.push_back(checkbox->panduan);
        }
        
        for (auto& checkbox : ccheckbox) {
            checkbox->panduan = false;
        }
    if (window) {
        window->recordundo([local_jilu, ccheckbox = this->ccheckbox]() {
            auto it = local_jilu.begin();
            for (auto box : ccheckbox) {
                box->panduan = *it;
                ++it;
            }
        });
    }
    }
};

class SelectAll {
    // ...
    list<shared_ptr<Checkbox>> ccheckbox;
    Window* window;
public:
    // TODO
    SelectAll(list<shared_ptr<Checkbox>> checkbox):ccheckbox(checkbox)
    {
         if(!ccheckbox.empty())
        {
            window=ccheckbox.front()->getParent();
        }
        else window=nullptr;
    }
    void operator()()
    {
        vector<bool> local_jilu;  
    
            for (auto& checkbox : ccheckbox) {
           local_jilu.push_back(checkbox->panduan);
        }
        
        for (auto& checkbox : ccheckbox) {
            checkbox->panduan = 1;
        }
    if (window) {
        window->recordundo([local_jilu, ccheckbox = this->ccheckbox]() {
            auto it = local_jilu.begin();
            for (auto box : ccheckbox) {
                box->panduan = *it;
                ++it;
            }
        });
    }
    }
};

class Submit {
    // ...
    list<shared_ptr<Checkbox>> ccheckbox;
public:
    // TODO
    Submit(list<shared_ptr<Checkbox>> checkbox):ccheckbox(checkbox){};
    void operator()()
    {
        for(auto it:ccheckbox)
        {
            if(it->panduan==0)
            {
                cout<<it->getName()<<" is not selected\n";
            }
            else
            {
                cout<<it->getName()<<" is selected\n";
            }
        }
    }
};