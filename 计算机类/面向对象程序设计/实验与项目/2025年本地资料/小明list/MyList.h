#pragma once
#include <list>
#include <memory>

class MyList
{
private:
	std::shared_ptr< std::list<int> > pt; // a pointer to the real container
	std::list<int>::iterator left, right; // the position of slice is [left, right). 'left' is included, 'right' is excluded.

	std::list<int>::iterator forward(int pos){
		// count from 'left', find the element at position 'pos'.
		auto now = left;
		while(pos--) now++;
		return now;
	}

public:
	MyList(): pt(new std::list<int>())
	{
		left = pt->begin();
		right = pt->end();
	}
	MyList(const MyList &obj): pt(obj.pt),left(obj.left),right(obj.right){}

	void append(int i){
		if(pt->empty())
		{
			pt->push_back(i);
			left=pt->begin();
			right=pt->end();
		}
		else{
			pt->insert(right, i);//insert i just before 'right'. 'right' and 'left' will be still valid (because we use list, not vector).
			// DEBUG !! Why I can't insert i??
		}
		
	}

	MyList operator()(int l,int r)
	{
		MyList slice;
		slice.pt=pt;
		auto start=forward(l);
		auto end=forward(r);
		slice.left=start;
		slice.right=end;
		return slice;
	}

	int& operator[](int pos){
		return *forward(pos); // access the element at the 'pos'
	}

	friend std::ostream& operator<<(std::ostream& out,const MyList& obj)
	{
		out << "[";
		if (obj.left != obj.right){
			auto now = obj.left;
			out << *now;
			now ++;
			for(; now != obj.right; now++){
				out << "," << *now;
			}
		}
		out << "]";
		return out;
	}

};