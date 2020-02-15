#include<iostream>
#include<vector>
#include<stack>
using namespace std;
template<class T> class mystack{
	vector<T> res;
public:
	void push(T a)
	{
		res.push_back(a);
	}
	void pop()
	{
		res.pop_back();
	}
	T top()
	{
		return res.back();
	}
	size_t size()
	{
		return res.size();
	}
	bool empty()
	{
		return res.empty();
	}
};
int main()
{
	mystack<int> sta;
	sta.push(1);
	sta.push(2);
	sta.push(3);
	sta.push(4);
	cout << sta.top() << endl;
	sta.pop();
	cout << sta.top() << endl;
	cout << sta.size() << endl;
	cout << sta.empty() << endl;
	return 0;
}

