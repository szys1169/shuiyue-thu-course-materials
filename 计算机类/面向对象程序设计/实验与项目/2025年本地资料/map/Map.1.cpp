#include"Map.h"
using namespace std;

Map::Map(int n):sz(n),capcity(0)
{
    data=new Pair[n];
}

int Map::size()
{
    return capcity;
}

int& Map::operator[](const string& name)
{
    for(int i=0;i<capcity;i++)
    {
        if(data[i].hasKey(name))
        {
            return data[i].getVal();
        }
    }
    data[capcity].reset(name,0);
    capcity++;
    return data[capcity-1].getVal();
}

int Map::operator[](const string& name) const
{
    for(int i=0;i<capcity;i++)
    {
        if(data[i].hasKey(name))
        {
            int a=data[i].getVal();
            return a;
        }
    }
    return 0;
}

Map::~Map()
{
    delete[] data;
}