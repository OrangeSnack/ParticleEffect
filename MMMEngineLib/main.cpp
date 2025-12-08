#include <iostream>

#include "Delegates.h"

using namespace MMMEngine;

int main()
{
	Func<int,int,int> del;

	del += [](int a, int b) {
		std::cout << "Lambda 1: " << a + b << std::endl;
		return a + b;
	};

	int num = del(2, 4);

	std::cout << "Result: " << num << std::endl;

	return 0;
}