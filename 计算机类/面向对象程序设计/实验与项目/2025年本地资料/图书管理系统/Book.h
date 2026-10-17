#pragma once
#include<iostream>
#include<string>
using namespace std;

template<class T>
class Book
{
    string name;
    string author;
    int page;
    public:
    Book(string Name,string Author,int Page):name(Name),author(Author),page(Page){};
    void show()
    {
        cout<<"Book name: "<<name<<", Author: "<<author<<", Pages: "<<page<<endl;
    }
    bool operator<(const Book<T>& other)
    {
        if(page<other.page)return true;
        return false;
    }
    string Name()
    {
        return name;
    }
};
