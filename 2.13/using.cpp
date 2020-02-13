#include<iostream>
using namespace std;
using it=int;
class A
{
	it a;
	it b;
public:
	A(it a,it b)
	{
		this->a = a;
		this->b = b;
	}
	friend int sum(A);
};

int sum(A a1)
{
	return a1.a + a1.b;
}
int main()
{
	A a(1, 2);
	cout << sum(a) << endl;
	return 0;
}