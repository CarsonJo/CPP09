# ifndef BITCOIN_HPP
# define BITCOIN_HPP
#include <map>
# include <iostream>
# include <exception>
# include <string>
# include <cstdlib>

class BitcoinExchange
{
	public :
		class Date
		{
			public :
				Date();
				Date(int year, int month, int day);
				Date(const Date &copy);
				~Date();
				void	operator=(const Date &a);
				bool	operator<(const Date &a) const;
				bool	operator==(const Date &a) const;
				static Date	extract_date(const std::string &date);

				int		get_year() const;
				int		get_month() const;
				int		get_day() const;
			private :
				static int	check_date(const std::string &date);
				static int	is_year(const std::string &year);
				static int	is_month(const std::string &month);
				static int	is_day(const std::string &day);
				int year;
				int month;
				int day;
		};
		static std::map<BitcoinExchange::Date, float>	DB;
};
std::ostream &operator<<(std::ostream &a, const BitcoinExchange::Date &b);
#endif