#include<iostream>
#include<vector>
#include<initializer_list>
#include<assert.h>

using namespace std;
using it=int;
class A
{
	int *a;
	int asize;
public:
	A(initializer_list<int> res)
	{
		asize = res.size();
		a = new int[asize];
		for (int i = 0; i < res.size(); i++)
		{
			*(a+i) = *(res.begin() + i);
		}
	}
	int& operator[](int n)
	{
		assert(n >= 0&& n<asize);
		return *(a+n);
	}
	
};

int main()
{
	A a({1,2,3,4,8});
	const int i = -2;
	static_assert(i > 0, "输出的不是a[2]");//此处提示错误，因为i<0
	a[i] = 5;
	cout << a[i] << endl;
	return 0;
}