#include<iostream>

using namespace std;
class A
{
public:
	char* name;
	int age;
	A(char* name, int age)
	{
		this->name = new char[20];
		strcpy(this->name, name);
		this->age = age;
	}
	~A()
	{
		delete name;
	}
	A(const A &a)
	{
	}
	A(A &&other) :age(other.age)
	{
		name = other.name;
		other.name = NULL;
	}
};
int main()
{
	A a("11",10);
	cout << a.name << endl;
	A b(std::move(a));
	return 0;
}