#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <typeinfo>
#include <sys/time.h>
#include "PmergeMe.hpp"

template <typename a>
void	test(char *argv[], int argc)
{
	a arr(0);

	for (int b = 1; b < argc; b++)
		arr.push_back(std::atoi(argv[b]));
	PmergeMe::pmerge(arr);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "not enough arg" << std::endl;

		return (1);
	}
	std::ostringstream	time1;
	std::ostringstream	time2;
	struct timeval		before;
	struct timeval		after;
	std::vector<int>	arr;
	std::deque<int>		arr2;
	std::deque<int> ret;

	for (int b = 1; b < argc; b++)
		arr.push_back(std::atoi(argv[b]));
	gettimeofday(&before, 0);
	PmergeMe::pmerge(arr);;
	gettimeofday(&after, 0);
	time1 << "Time to process a range of " << argc - 1 << " element with std::vector " <<
		(after.tv_sec * 1000000 - before.tv_sec * 1000000 ) + (after.tv_usec - before.tv_usec) << "us";


	for (int b = 1; b < argc; b++)
		arr2.push_back(std::atoi(argv[b]));
	gettimeofday(&before, 0);
	ret = PmergeMe::pmerge(arr2);;
	gettimeofday(&after, 0);
	time2 << "Time to process a range of " << argc - 1 << " element with std::deque " <<
		(after.tv_sec * 1000000 - before.tv_sec * 1000000 ) + (after.tv_usec - before.tv_usec) << "us";


	std::cout << "Before :";
	for (unsigned long int i = 0; i < arr.size(); i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
	std::cout << "After :";
	for (unsigned long int i = 0; i < arr.size(); i++)
		std::cout << ret[i] << " ";
	std::cout << std::endl;
	std::cout << time1.str() << std::endl << time2.str() << std::endl;
	for (unsigned long int i = 0; i < arr.size() - 1; i++)
	{
		if (ret[i] > ret[i + 1])
			std::cout << "DAMMMMMMMMNNNNNNNNNNN" << std::endl;
	}
}
