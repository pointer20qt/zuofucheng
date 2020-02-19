#include<iostream>
#include<vector>
#include<initializer_list>
#include<assert.h>
#include<memory>

using namespace std;

class tool
{
	char* a=nullptr;
public:
	tool()
	{
		cout << "构造了" << endl;
		a = new char[10];
	}
	~tool()
	{
		cout << "析构了" << endl;
		delete a;
	}
};
template <class T>
class myptr
{
	T* obj = nullptr;
public:
	myptr(T* a)
	{
		obj = a;
		a = nullptr;
	}
	myptr() = default;
	myptr(myptr &a)
	{
		obj = a.obj;
		a.obj = nullptr;
	}
	~myptr()
	{
		delete obj;
	}
	myptr& operator=(myptr& a)
	{
		delete obj;
		obj = a.obj;
		a.obj = nullptr;
		return *this;
	}
	T& operator*()
	{
		return *obj;
	}
	T* operator->()
	{
		return obj;
	}
	void reset(T* a=nullptr)
	{
		delete obj;
		obj = a;
	}
	T* get()
	{
		return obj;
	}
	T* release()
	{
		T* a = obj;
		obj=nullptr;
		return a;
	}
};


int main()
{
	tool *b = new tool;
	myptr<tool> ptr2(b);
	myptr<tool> ptr3;
	ptr3 = ptr2;
	cout << "hh" << endl;
	return 0;
}