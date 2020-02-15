#include<iostream>
#include<vector>
#include<initializer_list>
#include<assert.h>

using namespace std;
using it=int;
class A
{
	char *a;
public:
	int age;
	A(int age)
	{
		this->age = age;
		a = new char[10];
	}
	A(const A &res)
	{
		age = res.age;
		a = new char[10];
	}
	A(A &&res)
	{
		age = res.age;
		a = res.a;
		res.a = nullptr;
	}
	~A()
	{
		delete a;
	}
	A operator=(A &res)
	{
		this->age = res.age;
		delete res.a;
		res.a = new char[10];
		return res;
	}
	A operator=(A &&res)
	{
		this->age = res.age;
		this->a=res.a;
		res.a = nullptr;
		return *this;
	}
};
template <class T> void myswap(T &a,T& b)
{
	T tem=std::move(a);
	a = std::move(b);
	b = std::move(tem);
}
template <class T, class ...arg>void my(T t, arg ...d)
{
	cout << t << " ";
	my(d...);
}
void my()
{
	cout << endl;
	cout << "参数包解析完了" << endl;
}
int main()
{
	A a(10);
	A b(20);
	myswap(a, b);
	cout << "交换后：" << a.age <<"  "<< b.age << endl;

	my(5, 3.0,"123", 8);
	return 0;
}