#include<iostream>
#include<vector>
#include<stack>
#include<memory>
using namespace std;
template <class T>
class Ref
{
	T* ref = nullptr;
	int rcount = 0;
	int wcount = 0;
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
	void wincrease()
	{
		wcount++;
	}
	void reduce()
	{
		rcount--;
		if (rcount == 0)
		{
			delete ref;
			if (wcount == 0)
			{
				delete this;
			}
		}
	}
	void wreduce()
	{
		wcount--;
		if (wcount == 0&& rcount==0)
		{
			delete this;
		}
	}
	T* get()
	{
		return ref;
	}
};

template<class T> class myweak_ptr;
template<class T>
class myshared_ptr
{
	friend class myweak_ptr<T>;
	Ref<T>* obj = nullptr;
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
		cout << "myshared_ptr拷贝构造" << endl;
		obj = a.obj;
		obj->increase();
	}
	myshared_ptr(myshared_ptr&& a)
	{
		cout << "myshared_ptr移动构造" << endl;
		obj = a.obj;
		a.obj = nullptr;
	}
	myshared_ptr& operator=(const myshared_ptr& a)
	{
		cout << "myshared_ptr拷贝赋值" << endl;
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
		cout << "myshared_ptr移动赋值" << endl;
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
	void reset(T* a = nullptr)
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
template<class T>
class myweak_ptr
{
	Ref<T> *obj = nullptr;
public:
	myweak_ptr() = default;
	~myweak_ptr()
	{
		if (obj)
		{
			obj->wreduce();
		}
	}
	myweak_ptr(myshared_ptr<T>& a)
	{
		obj = a.obj;
		obj->wincrease();
	}
	myweak_ptr(const myweak_ptr& a)
	{
		obj = a;
		obj->wincrease();
	}
	myweak_ptr(myweak_ptr&& a)
	{
		obj = a;
		a = nullptr;
	}
	myweak_ptr& operator=(const myweak_ptr& a)
	{
		if (obj)
		{
			obj->wreduce();
		}
		obj = a.obj;
		obj->wincrease();
		return *this;
	}
	myweak_ptr& operator=(myweak_ptr&& a)
	{
		if (obj)
		{
			obj->wreduce();
		}
		obj = a.obj;
		a.obj = nullptr;
		return *this;
	}
	myshared_ptr<T> lock()
	{
		myshared_ptr<T> tem;
		tem.obj = obj;
		return tem;
	}
	void reset(myweak_ptr& a=nullptr)
	{
		if (obj)
		{
			obj->wreduce();
		}
		obj = a.obj;
	}
	int wCount()
	{
		if (obj)
		{
			return obj->getCount();
		}
		return 0;
	}
};

struct ListNode
{
	myweak_ptr<ListNode> pre;
	myweak_ptr<ListNode> next;
	~ListNode()
	{
		cout << "~~ListNode" << endl;
	}
};
void run()
{
	ListNode* node1 = new ListNode;
	ListNode* node2 = new ListNode;
	myshared_ptr<ListNode> ptr1(node1);
	myshared_ptr<ListNode> ptr2(node2);
	ptr1->next = ptr2;
	ptr2->pre = ptr1;
}

int main()
{
	run();
	char* a = new char[10];
	myshared_ptr<char> ptr1(a);
	cout << ptr1.my_count() << endl;
	myweak_ptr<char> pre(ptr1);
	myshared_ptr<char> ptr3(pre.lock());
	cout << ptr1.my_count() << endl;
	/*char* b = new char[10];
	shared_ptr<char> s(b);
	weak_ptr<char> w(s);
	shared_ptr<char> s2=w.lock();
	cout << s.use_count() << endl;*/
	return 0;
}

