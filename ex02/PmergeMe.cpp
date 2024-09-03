#include "PmergeMe.hpp"

SequenceSort::SequenceSort() : i(pow(2, 1) - 1), j(1)
{

}

SequenceSort::SequenceSort(int a) : i(pow(2, a) - 1), j(a)
{

}

SequenceSort::~SequenceSort()
{

}

SequenceSort::operator int(void)
{
	return (i);
}

void	SequenceSort::next()
{
	j++;
	i = pow(2, j) - 1;
}

unsigned long int	SequenceSort::value()
{
	return (i);
}

static int		binary_insert(std::vector<Pair<std::vector> *> &to_recieve, Pair<std::vector> *to_insert, int max)
{
	int	mid = std::floor(max / 2.0 + 0.5);
	int min = 0;

	while (min <= max)
	{
		if (to_recieve[mid]->value() >= to_insert->value())
			max = mid - 1;
		else
			min = mid + 1;
		mid = min + (max - min) / 2;
	}
	to_recieve.insert(to_recieve.begin() + mid, to_insert);
	return (mid);
}

static void		insert(std::vector<Pair<std::vector> *> &arr, unsigned long int true_size, Pair<std::vector> *last)
{
	SequenceSort		i(2);
	unsigned long int	k = 1;
	unsigned long int	min = SequenceSort(1) + 1;
	int					temp;
	unsigned long int	max;
	unsigned long int	top = arr.size() - 1;
	int					depth = arr[top]->depth();

	binary_insert(arr, arr[0]->get_arr().back(), 0);
	arr[1]->get_arr().pop_back();
	arr[1]->depth_down();
	while (k < true_size)
	{
		max = i.value();
		if (max < arr.size())
			top = max;
		else
			top = arr.size() - 1;
		temp = 0;
		while (min < max + 1 && k < true_size)
		{
			while (arr[top]->depth() != depth)
				top--;
			binary_insert(arr, arr[top]->get_arr().back(), top - 1);
			arr[top + 1]->get_arr().pop_back();
			arr[top + 1]->depth_down();
			min++;
			temp++;
			k++;
		}
		min += temp;
		i.next();
	}
	if (last)
		binary_insert(arr, last, arr.size() - 1);
}

static void	split(std::vector<Pair<std::vector> *> &arr, int size)
{
	Pair<std::vector>	*last = 0;
	int					i = 0;

	while (i < size / 2)
	{
		if (arr[i]->value() > arr[size - i - 1]->value())
		{
			arr[i]->get_arr().push_back(arr[size - i - 1]);
			arr.pop_back();
			arr[i]->depth_up();
		}
		else
		{
			arr[size - i - 1]->get_arr().push_back(arr[i]);
			arr[i] = arr[size - i - 1];
			arr.pop_back();
			arr[i]->depth_up();
		}
		i++;
	}
	if (size % 2)
	{
		last = arr[i];
		arr.pop_back();
	}
	if (size / 2.0 >= 2)
		split(arr, size / 2.0);
	insert(arr, size / 2.0, last);
}

std::vector<int>	PmergeMe::pmerge(std::vector<int> arr)
{
	std::vector<Pair<std::vector> >		a;
	std::vector<int>					ret(arr.size());
	std::vector<Pair<std::vector> *>	to_use(arr.size());
	std::vector<int >::iterator			b = arr.begin();

	while (b != arr.end())
	{
		a.push_back(Pair<std::vector>(*b, 0));
		b++;
	}
	for(unsigned long int i = 0; i < a.size(); i++)
		to_use[i] = &a[i];
	split(to_use, arr.size());
	for (unsigned long int i = 0; i < arr.size(); i++)
		ret[i] = to_use[i]->value();
	return (ret);
}
//LISTTTTTTTTTTTTTTTTT

static int		binary_insert(std::deque<Pair<std::deque> *> &to_recieve, Pair<std::deque> *to_insert, int max)
{
	int	mid = std::floor(max / 2.0 + 0.5);
	int min = 0;

	while (min <= max)
	{
		if (to_recieve[mid]->value() >= to_insert->value())
			max = mid - 1;
		else
			min = mid + 1;
		mid = min + (max - min) / 2;
	}
	to_recieve.insert(to_recieve.begin() + mid, to_insert);
	return (mid);
}

static void		insert(std::deque<Pair<std::deque> *> &arr, unsigned long int true_size, Pair<std::deque> *last)
{
	SequenceSort		i(2);
	unsigned long int	k = 1;
	unsigned long int	min = SequenceSort(1) + 1;
	int					temp;
	unsigned long int	max;
	unsigned long int	top = arr.size() - 1;
	int					depth = arr[top]->depth();

	binary_insert(arr, arr[0]->get_arr().back(), 0);
	arr[1]->get_arr().pop_back();
	arr[1]->depth_down();
	while (k < true_size)
	{
		max = i.value();
		if (max < arr.size())
			top = max;
		else
			top = arr.size() - 1;
		temp = 0;
		while (min < max + 1 && k < true_size)
		{
			while (arr[top]->depth() != depth)
				top--;
			binary_insert(arr, arr[top]->get_arr().back(), top - 1);
			arr[top + 1]->get_arr().pop_back();
			arr[top + 1]->depth_down();
			min++;
			temp++;
			k++;
		}
		min += temp;
		i.next();
	}
	if (last)
		binary_insert(arr, last, arr.size() - 1);
}

static void	split(std::deque<Pair<std::deque> *> &arr, int size)
{
	Pair<std::deque>	*last = 0;
	int					i = 0;

	while (i < size / 2)
	{
		if (arr[i]->value() > arr[size - i - 1]->value())
		{
			arr[i]->get_arr().push_back(arr[size - i - 1]);
			arr.pop_back();
			arr[i]->depth_up();
		}
		else
		{
			arr[size - i - 1]->get_arr().push_back(arr[i]);
			arr[i] = arr[size - i - 1];
			arr.pop_back();
			arr[i]->depth_up();
		}
		i++;
	}
	if (size % 2)
	{
		last = arr[i];
		arr.pop_back();
	}
	if (size / 2.0 >= 2)
		split(arr, size / 2.0);
	insert(arr, size / 2.0, last);
}

std::deque<int>	PmergeMe::pmerge(std::deque<int> arr)
{
	std::deque<Pair<std::deque> >		a;
	std::deque<int>						ret(arr.size());
	std::deque<Pair<std::deque> *>	to_use(arr.size());
	std::deque<int >::iterator	b = arr.begin();

	while (b != arr.end())
	{
		a.push_back(Pair<std::deque>(*b, 0));
		b++;
	}
	for(unsigned long int i = 0; i < a.size(); i++)
		to_use[i] = &a[i];
	split(to_use, arr.size());
	for (unsigned long int i = 0; i < arr.size(); i++)
		ret[i] = to_use[i]->value();
	return (ret);
}