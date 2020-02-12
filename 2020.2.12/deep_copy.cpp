#include<iostream>
#include<vector>
using namespace std;
class A
{
public:
	char* name;
	A()
	{
		this->name = new char(10);
	}
	A(const A &b)
	{
		name = new char(10);
	}
	~A()
	{
		delete name;
		cout << "Îö¹¹ÁË" << endl;
	}
};


int main()
{ 
	A a1;
	A a2(a1);
	return 0;
}