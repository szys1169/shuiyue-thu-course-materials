#pragma once
#include <bits/stdc++.h>
#include <iostream>
#include<typeinfo>
#include<memory>
#include <utility>
#include <type_traits>

class PyObject 
{
	void* ptr = nullptr;
	int tp = 0;
	std::function<void(void*)> del;
public:
	
	void operator=(char v) {
		std::cout << "PyObject got a value" << std::endl;
		if (tp) del(ptr);
		ptr = new char;
		del = [](void* p){ delete (char*)p; };
		*(char*)ptr = v;
		tp = 2;
	}
	
	void operator=(int v) {
		std::cout << "PyObject got a value" << std::endl;
		if (tp) del(ptr);
		ptr = new int;
		del = [](void* p){ delete (int*)p; };
		*(int*)ptr = v;
		tp = 3;
	}
	
	void operator=(double v) {
		std::cout << "PyObject got a value" << std::endl;
		if (tp) del(ptr);
		ptr = new double;
		del = [](void* p){ delete (double*)p; };
		*(double*)ptr = v;
		tp = 4;
	}
	
	template<typename T>
	void operator=(T& v) {
		std::cout << "PyObject got a value" << std::endl;
		if (tp) del(ptr);
		ptr = &v;
		tp = 0;
		std::cout << "Borrowing" << std::endl;
	}
	
	template<typename T>
	void operator=(T&& v) {
		std::cout << "PyObject got a value" << std::endl;
		if (tp) del(ptr);
		ptr = new T(std::move(v));
		del = [](void* p){ delete (T*)p; };
		tp = 1;
		std::cout << "Owning" << std::endl;
	}
	
	void operator=(PyObject& p) {
		std::cout << "PyObject got a value" << std::endl;
		if (tp) del(ptr);
		tp = p.tp;
		if (p.tp == 4) *this = (double)p; else
		if (p.tp == 3) *this = (int)p; else
		if (p.tp == 2) *this = (char)p; else
		if (p.tp == 1) {
			ptr = p.ptr;
			del = p.del;
			p.tp = 0;
			std::cout << "Owning" << std::endl;
		} else {
			ptr = p.ptr;
			std::cout << "Borrowing" << std::endl;
		}
	}
	
	void operator=(PyObject* p) {
		std::cout << "PyObject got a value" << std::endl;
		if (tp) del(ptr);
		ptr = p->ptr;
		tp = 0;
		std::cout << "Borrowing" << std::endl;
	}
	
	template<typename T>
	operator T&() const { return *(T*)ptr; }
	
	//~PyObject() { if (tp) del(ptr); }
};
