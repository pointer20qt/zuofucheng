#include<iostream>
#include<vector>
#include<stack>
#include<memory>
using namespace std;
template <class T> 
class Ref
{
	T* ref=nullptr;
	int rcount = 0;
public:
	Ref() = default;
	Ref(T* a)
	{
		ref = a;
		rcount++;
	}
	int getCount()
	{
		return rcount;
	}
	void increase()
	{
		rcount++;
	}
	void reduce()
	{
		rcount--;
		if (rcount == 0)
		{
			cout << "Îö¹¹ÁË" << endl;
			delete ref;
			delete this;
		}
	}
	T* get()
	{
		return ref;
	}
};
template<class T> 
class myshared_ptr
{
	Ref<T>* obj=nullptr;
public:
	myshared_ptr() = default;
	myshared_ptr(T* a)
	{
		obj = new Ref<T>(a);
	}
	~myshared_ptr()
	{
		if (obj)
		{
			obj->reduce();
		}
	}
	myshared_ptr(const myshared_ptr& a)
	{
		obj = a.obj;
		obj->increase();
	}
	myshared_ptr(myshared_ptr&& a)
	{
		obj = a.obj;
		a.obj = nullptr;
	}
	myshared_ptr& operator=(const myshared_ptr& a)
	{
		if (obj != nullptr)
		{
			obj->reduce();
		}
		obj = a.obj;
		obj->increase();
		return *this;
	}
	myshared_ptr& operator=(myshared_ptr&& a)
	{
		if (obj != nullptr)
		{
			obj->reduce();
		}
		obj = a.obj;
		a.obj = nullptr;
		return *this;
	}
	int my_count()
	{
		if (obj != nullptr)
		{
			return obj->getCount();
		}
		return 0;
	}
	void reset(T* a=nullptr)
	{
		if (obj != nullptr)
		{
			obj->reduce();
		}
		if (a == nullptr)
		{
			obj = nullptr;
		}
		else
		{
			obj = new Ref<T>(a);
		}
	}
	void release()
	{
		if (obj)
		{
			obj->reduce();
		}
		obj = nullptr;
	}
	T* get()
	{
		if (obj)
		{
			return obj->get();
		}
		return (T*)nullptr;
	}
	T& operator*()
	{
		return *obj->get();
	}
	T* operator->()
	{
		return obj->get();
	}
};
class A
{
	char* b = nullptr;
public:
	A()
	{
		b = new char[10];
	}
	void run()
	{
		cout << "run" << endl;
	}
};
int main()
{
	A *c=new A();
	char* a = new char[10];
	myshared_ptr<A> ptr(c);
	cout << ptr.my_count() << endl;
	myshared_ptr<A> ptr2(std::move(ptr));
	cout << ptr.my_count() << endl;
	myshared_ptr<A> ptr3;
	ptr3 = ptr2;
	cout << ptr2.my_count() << endl;
	return 0;
}

