#pragma once
#include <iostream>
#include <vector>
using namespace std;

template<class T, int N>
class MultiArray
{
	int shuliang[N];
	vector<vector<T>> shuju; 
public:
	MultiArray()
	{
		for(i=0;i<N;i++)
		{
			shuliang[i]=0;
		}
	}
	~MultiArray();
	MultiArray(const vector<int> &dims, const vector<T> &data = vector<T>())
	{
		if(dims.size()==0)
		{
			shuliang[0]=data.size()-N+1;
			for(int i=1;i<N;i++){shuliang[i]=1;}
		}
		else if(dim.size()<N)
		{
			for(int i=0;i<dim.size();i++){shuliang[i]=dim[i];}
			for(int i=dim.size();i<N;i++){shuliang[i]=1;}
		}
		else
		{
			for(int i=0;i<dim.size();i++){shuliang[i]=dim[i];}
		}
		if(data.size()==0)
		{
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<shuliang[i];j++)
				{
					shuju[i].push_back(T());
				}
			}
		}
		else
		{
			int counnt=0;
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<shuliang[i];j++)
				{
					shuju[i].push_back(data[count]);
					count++;
				}
			}
		}
	}
	void set(const vector<int> &idx, const T &val)
	{
		shuju[idx[0]][idx[1]]=val;
	}
	T& get(const vector<int> &idx)
	{
		return *shuju[idx[0]][idx[1]];
	}
	vector<int>& get_dims()
	{
		vector<int> a;
		for(int i=0;i<N;i++)
		{
			a.push_back(shuliang[i]);
		}
		return *a;
	}

	template<int M>
	bool operator==(const MultiArray<T, M> &other) const;
	template<int M>
	bool operator!=(const MultiArray<T, M> &other) const;
	MultiArray& operator=(const MultiArray<T, N> &other);

	class Iterator {
	public:
		Iterator(const MultiArray* arr, int idx);
		T operator*() const;
		Iterator& operator++();
		Iterator operator++(int);
		bool operator!=(const Iterator& other) const;
		bool operator==(const Iterator& other) const;
		Iterator& operator=(const Iterator& other);
	};
	Iterator begin() const;
	Iterator end() const;

	auto operator[] (const int &idx);
	auto operator[] (const int &idx) const;

	void reshape(const vector<int> &dims2);
	void resize(const vector<int> &dims2);
};

template<class T, int N>
std::ostream& operator << (std::ostream &out, const MultiArray<T, N> &a);