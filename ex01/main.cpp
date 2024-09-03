#include <iostream>
#include "RPN.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "wrong arg number" << std::endl;
		return (0);
	}
	try
	{
		RPN	a(argv[1]);

		std::cout << a.calcul() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}