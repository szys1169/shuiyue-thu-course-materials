#pragma once
#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <unordered_set>
#include <vector>
#include <stack>

template<class T>
class Data
{
protected:
    int length;
public:
    Data(int _length) : length(_length) {}
    int get_length()
    {
        return length;
    }
    virtual int get_index()=0;
    virtual const T& get(int index) = 0;
    virtual std::shared_ptr<Data<T>> parent() const = 0;
    virtual std::shared_ptr<Data<T>> parent2() const = 0;
    virtual ~Data() = default; 
};

template<class T>
class DataEmpty : public Data<T>
{
public:
    DataEmpty<T>(): Data<T>(0) {};
    const T& get(int index) {
        assert(0); // No data in DataEmpty
    }
    int get_index()
    {
        return -1;
    }
    std::shared_ptr<Data<T>> parent()const override {
        return nullptr;
    }
    std::shared_ptr<Data<T>> parent2()const override {
        return nullptr;
    }
};

template<class T>
class DataPushBackDecorator : public Data<T>
{
    std::shared_ptr<Data<T>> parent_data;
    T value;
    public:
    DataPushBackDecorator(std::shared_ptr<Data<T>> parent, const T& val)
             :Data<T>(parent->get_length()+1), parent_data(parent),value(val){}
    const T& get(int index) 
    {
         if (index == parent_data->get_length()) {
            return value;
        }
        return parent_data->get(index);
    }
    int get_index()
    {
        return parent_data->get_length();
    }
    std::shared_ptr<Data<T>> parent()const override 
    {
        return parent_data;
    }
     std::shared_ptr<Data<T>> parent2()const override 
    {
        return parent_data;
    }
    // Implement a Decorator for push_back operation
};

template<class T>
class DataSetDecorator : public Data<T>
{
    std::shared_ptr<Data<T>> parent_data;
    int set_index;
    T value;
    public:
    DataSetDecorator(std::shared_ptr<Data<T>> parent, int index, const T& val)
        : Data<T>(parent->get_length()), parent_data(parent), set_index(index), value(val) {}
    const T& get(int index) override {
        if (index == set_index) {
            return value;
        }
        return parent_data->get(index);
    }
    int get_index()
    {
        return set_index;
    }
    std::shared_ptr<Data<T>> parent()const override 
    {
        return parent_data;
    }
     std::shared_ptr<Data<T>> parent2()const override 
    {
        return parent_data;
    }
    // Implement a Decorator for set operation
};


template<class T>
class DataupdateDecorator: public Data<T>
{
    std::shared_ptr<Data<T>> parent_data;
    std::shared_ptr<Data<T>> parent2_data;
    std::shared_ptr<Data<T>> com;
    public:
    DataupdateDecorator(std::shared_ptr<Data<T>> parent, std::shared_ptr<Data<T>> parent2,std::shared_ptr<Data<T>> common)
             :Data<T>(std::max(parent->get_length(),parent2->get_length())), parent_data(parent),parent2_data(parent2),com(common){}
    const T& get(int index) 
    {
        std::shared_ptr<Data<T>>a= parent_data;
        while(a!=com&&a)
        {
            int ind=a->get_index();
            if(ind==index)
            {
                return parent_data->get(index);
            }
            a=a->parent();
        }
        return parent2_data->get(index);
    }
    int get_index()
    {
        return -2;
    }
    std::shared_ptr<Data<T>> parent()const override 
    {
        return parent_data;
    }
    std::shared_ptr<Data<T>> parent2()const override 
    {
        return parent2_data;
    }
    // Implement a Decorator for push_back operation
};

template<class T>
class PVector
{
public:
    std::shared_ptr<Data<T>> data;

    PVector() : data(std::make_shared<DataEmpty<T>>()) {}
    PVector(std::shared_ptr<Data<T>> _data) : data(_data) {}

    PVector<T> push_back(const T &value) const{
        return PVector<T>(std::make_shared<DataPushBackDecorator<T>>(data, value));
    }
    PVector<T> set(int index, const T &value) const{
        return PVector<T>(std::make_shared<DataSetDecorator<T>>(data, index, value));
    }

    PVector<T> undo() const 
    {
        auto parent_data = data->parent();
        if (parent_data == nullptr) {
            std::cout << "cannot undo" << std::endl;
            return *this;
        }
        return PVector<T>(parent_data);
    }

    std::shared_ptr<Data<T>> common(std::shared_ptr<Data<T>> a, std::shared_ptr<Data<T>> b) const 
    {
        while(a)
        {
            std::shared_ptr<Data<T>>c=b;
            while(c)
            {
                if(a==c)return c;
                c=c->parent();
            }
            a=a->parent();
        }
        return nullptr;
    }

    bool panduan(std::shared_ptr<Data<T>> a, std::shared_ptr<Data<T>> b,std::shared_ptr<Data<T>> c) const 
    {
        while(a!=c&&a)
        {
            std::shared_ptr<Data<T>>d=b;
            while(d!=c&&d)
            {
                if(a->get_index()==-2)
                {
                    if(!panduan(a->parent2(),d,c))
                    {return false;}
                }
                else if(a->get_index()==d->get_index())
                {
                    return false;
                }
                if(d->get_index()==-2)
                {
                    if(!panduan(d->parent2(),a,c))
                    {return false;}
                }
                d=d->parent();
            }
            a=a->parent();
        }
        return true;
    }

    PVector<T> update(PVector<T> a) const 
    {
        std::shared_ptr<Data<T>> com=common(data,a.data);
        if(!com)
        {
            std::cout<<"cannot update: no origin found"<<std::endl;
            return *this;
        }
        if(!panduan(data,a.data,com))
        {
            std::cout<<"cannot update: conflicts found"<<std::endl;
            return *this;
        }
        return PVector<T>(std::make_shared<DataupdateDecorator<T>>(data,a.data,com));
    }

    const T& operator[](int index){
        return data->get(index);
    }

    friend std::ostream& operator<<(std::ostream& out, const PVector& p) {
        out << "[";
        if(p.data->get_length()>=1)
            out << p.data->get(0);
        for (int i = 1; i < p.data->get_length(); ++i) {
            if (i > 0) {
                out << ", ";
            }
            out << p.data->get(i);
        }
        out << "]";
        return out;
    }
};
