#include <thread>
#include <future>
#include <iostream>

using namespace std;

void Func(promise<long long int> *p1, promise<long long int> *p2)
{
	long long int res = 1;
	for (long long int i = 2; i <= 20; i++)
	{
		res *= i;
	}
	p1->set_value(res);

	long long int fib1 = 1;
	long long int fib2 = 1;
	long long int fib = 0;

	for (long long int i = 3; i < 100; i++)
	{
		fib = fib1 + fib2;
		fib2 = fib1;
		fib1 = fib;
	}
	p2->set_value(fib);
}

int main()
{
	promise<long long int> p1;
	promise<long long int> p2;
	thread t(Func, &p1, &p2);
	future<long long int> f1 = p1.get_future();
	cout << "Factorial = " << f1.get() << endl;
	future<long long int> f2 = p2.get_future();
	cout << "Fibanacci = " << f2.get() << endl;
	t.join();
	cout << "thread end" << endl;
	system("pause");
	return 0;
}