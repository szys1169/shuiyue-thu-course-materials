#pragma once
#include<iostream>
#include<vector>
#include"Book.h"

using namespace std;

template<class T>
class Library
{
    vector<Book<T>> books;
    public:
    Library(){};
    void addBook(const Book<T>& book) 
    {
        books.push_back(book);
    }
    void show()
    {
        for(auto a:books)
        {
            a.show();
        }
    }
    void borrowBook(const std::string& title)
    {
        for(auto a:books)
        {
            if(a.Name()==title)
            {
                cout<<"Books Checked out "<<title<<"."<<endl;
                return ;
            }
        }
        cout<<"Book "<<title<<" does not exist."<<endl;
    }
};