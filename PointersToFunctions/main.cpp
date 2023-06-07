#include<iostream>
using namespace std;

void hello()
{
	cout << "hello" << endl;
}
int sum(int a, int b)
{
	return a + b;
}

void main()
{
	setlocale(LC_ALL, "");
	cout << main << endl;
	hello;

	void (*p_hello)() = hello;
	(*p_hello)();

//	cout << sum(2, 3) << endl;

	int(* p_sum)(int a, int b) = sum;
	cout << p_sum(2, 3) << endl;
}