#ifndef RPN_hpp
# define RPN_hpp
# include <string>
# include <list>
# include <stack>
# include <algorithm>
# include <exception>
# include <iostream>
class RPN
{
	public :

		class NotRpn : public std::exception
		{
			public :
				const char * what() const throw();
		};
		class DivideZero : public std::exception
		{
			public :
				const char * what() const throw();
		};
		RPN(const std::string &rpn);
		~RPN();

		static bool	check_rpn(const std::string &rpn);
		int			calcul();
		int			make_op(int a, int b, char op);

	private :

		RPN();
		RPN(const RPN &to_copy);
		void operator=(const RPN &to_copy);

		static std::list<char>	op;
		std::string				rpn;
};
#endif
