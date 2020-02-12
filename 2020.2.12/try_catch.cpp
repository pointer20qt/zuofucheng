#include<iostream>
#include<vector>
using namespace std;
void main()
{
	vector<int> a = {1,2,3,4,5};
	try{
		//a.at(6);
		throw 2;
	}
	catch (int){
		cout << "int" << endl;
	}
	catch (out_of_range e){
		cout << "Ô½½çÁË" <<endl;
	}
	catch (...){
		cout << "..." << endl;
	}

}
