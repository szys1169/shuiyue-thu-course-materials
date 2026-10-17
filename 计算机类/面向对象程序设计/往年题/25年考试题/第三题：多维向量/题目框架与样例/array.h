#pragma once
#include <iostream>
#include <vector>
using namespace std;

template<class T, int N>
class MultiArray {
public:
	MultiArray();
	~MultiArray();
	MultiArray(const vector<int> &dims, const vector<T> &data = vector<T>());
	void set(const vector<int> &idx, const T &val);
	T& get(const vector<int> &idx);
	vector<int>& get_dims();

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