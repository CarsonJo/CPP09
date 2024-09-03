#ifndef PmergeMe_hpp
# define PmergeMe_hpp
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>

template<template <class b, class c = std::allocator<b> > class a>
class Pair
{
	public :

		Pair() throw() : val(0), d(0), link(0){};
		Pair(int v, int d) : val(v), d(d), link(0){};
		Pair(int v, int d, a<Pair *> to_copy) : val(v), d(d), link(to_copy){};
		Pair(const Pair & to_copy) throw(): val(to_copy.val), d(to_copy.d), link(to_copy.link){};
		~Pair(){};
		void	operator=(const Pair& to_copy){
			val = to_copy.val;
			d = to_copy.d;
			link = to_copy.link;
		};

		a<Pair *>	&get_arr(){return (link);};
		int			value() const{return (val);};
		int			depth() const{return (d);};
		void		depth_down(){d--;};
		void		depth_up(){d++;};

	private :

		int			val;
		int			d;
		a<Pair *>	link;
};

class PmergeMe
{
	public :
		static std::vector<int> pmerge(std::vector<int> arr);
		static std::deque<int> pmerge(std::deque<int> arr);
	private :
		PmergeMe();
		PmergeMe(const PmergeMe &to_copy);
		~PmergeMe();

		void operator=(const PmergeMe &to_copy);
};

class SequenceSort
{
	private :
		unsigned long int	i;
		int	j;
		SequenceSort(const SequenceSort &to_copy);
		void	operator=(const SequenceSort &to_copy);
	public :
		SequenceSort();
		SequenceSort(int a);
		~SequenceSort();
		operator int();
		void				next();
		unsigned long int	value();
};
#endif
