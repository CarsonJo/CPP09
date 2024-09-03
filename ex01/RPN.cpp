#include "RPN.hpp"

std::list<char>	fill_op();

std::list<char>	RPN::op = fill_op();

std::list<char>	fill_op()
{
	std::list<char> op;

	op.push_front('+');
	op.push_front('-');
	op.push_front('*');
	op.push_front('/');
	return (op);
}


RPN::RPN(const std::string &rpn)
{
	if (!check_rpn(rpn))
		throw(NotRpn());
	std::string::iterator	a;

	this->rpn = rpn;
	a = this->rpn.begin();
	while (a != this->rpn.end())
	{
		if (std::isspace(*a))
			a = this->rpn.erase(a);
		else
			a++;
	}
}

RPN::~RPN()
{

}


int	RPN::make_op(int a, int b, char op)
{
	if (op == '+')
		return (a + b);
	else if (op == '-')
		return (a - b);
	else if (op == '*')
		return (a * b);
	else if (op == '/')
	{
		if (b == 0)
			throw(DivideZero());
		return (a / b);
	}
	return (0);
}

int	RPN::calcul()
{
	std::list<int>		st;
	std::string::iterator	a = rpn.begin();
	int					b, c;

	while (a != rpn.end())
	{
		if (std::isdigit(*a))
			st.push_front(*a - '0');
		else
		{
			c = st.front();
			st.pop_front();
			b = st.front();
			st.pop_front();
			st.push_front(make_op(b, c, *a));
		}
		a++;
	}
	return (st.front());
}

bool	RPN::check_rpn(const std::string &rpn)
{
	std::string::const_iterator a = rpn.begin();
	int							op = 0;
	int							number = 0;

	while (a != rpn.end())
	{
		if (std::isdigit(*a))
			number++;
		else if (std::find(RPN::op.begin(), RPN::op.end(), *a) != RPN::op.end())
		{
			op++;
			if (op >= number)
				return (0);
		}
		else if (!std::isspace(*a))
			return (0);
		a++;
	}
	if (op != number -1)
			return(0);
	return (1);
}

const char *	RPN::NotRpn::what() const throw()
{
	return ("format error string not rpn.");
}

const char *	RPN::DivideZero::what() const throw()
{
	return ("division by zero");
}