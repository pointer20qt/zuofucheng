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
		cout << "����������" << endl;
	}
	virtual void print() //��̬
	{
		cout << "����print" << endl;
	}
	void hh()
	{
		cout << "hh����" << endl;
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
		cout << "��������" << endl;
	}
	virtual void print() //������
	{
		cout << "����print" << endl;
	}
	void hh() //����
	{
		cout << "hh����" << endl;
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