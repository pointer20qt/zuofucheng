#include<iostream>
using namespace std;
using it=int;
class A
{

	char *name;
public:
	A(char* name)
	{
		this->name = new char[10];
		strcpy(this->name, name);
	}
	A()
	{
		this->name = new char[10];
	}
	virtual ~A()
	{
		delete[] name;
		cout << "父类析沟了" << endl;
	}
	virtual void print() //多态
	{
		cout << "父类print" << endl;
	}
	void hh()
	{
		cout << "hh父类" << endl;
	}
};
class B:public A
{
	char* address;
public:
	B()
	{
		address = new char[10];
	}
	virtual ~B()
	{
		delete[]address;
		cout << "子类析构" << endl;
	}
	virtual void print() //虚析构
	{
		cout << "子类print" << endl;
	}
	void hh() //隐藏
	{
		cout << "hh子类" << endl;
	}
};

int main()
{
	B b;
	A *a=&b;
	a->print();
	b.hh();
	return 0;
}