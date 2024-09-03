#include <iostream>
#include <map>
# include <map>
# include <cstdlib>
# include <fstream>
#include <algorithm>
# include <cctype>
#include "BitcoinExchange.hpp"

static bool	is_value(std::string &sub)
{
	if (sub.find_first_not_of("0123456789.") != std::string::npos)
		return (0);
	float a = std::strtod(sub.c_str(), 0);

	if (a > 1000 || a < 0)
		return (0);
	return (1);
}

static void	print_value(BitcoinExchange::Date &date, float numb)
{
	std::map<BitcoinExchange::Date, float>::iterator a = BitcoinExchange::DB.upper_bound(date);

	if (a == BitcoinExchange::DB.begin() || a == BitcoinExchange::DB.end())
	{
		std::cerr << "not valid time : " << date << std::endl;
		return ;
	}
	a--;
	std::cout << date << "(" << a->first << ") => " << numb << " = " << numb * a->second << std::endl;
}

static void	remove_space(std::string &str)
{
	std::string::iterator	a = str.begin();

	while (a != str.end())
	{
		if (*a == ' ')
			a = str.erase(a);
		else
			a++;
	}
}

static void	loop_file(std::fstream &fd, std::string &sub)
{
	std::map<BitcoinExchange::Date, float>	ret;
	std::string								sub2;
	BitcoinExchange::Date					temp;

	while (std::getline(fd, sub))
	{
		if (sub.find('|') == std::string::npos)
		{
			std::cerr << "format error::" << sub << std::endl;
			continue ;
		}
		try
		{
			sub2 = sub.substr(0, sub.find('|'));
			remove_space(sub2);
			temp = BitcoinExchange::Date::extract_date(sub2);
			sub2 = sub.substr(sub.find('|') + 1);
			remove_space(sub2);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << "::" << sub2 << std::endl;
			continue ;
		}
		if (!is_value(sub2))
		{
			std::cerr << "error bad value::" << sub2 << std::endl;
			continue ;
		}
		print_value(temp, std::strtod(sub2.c_str(), 0));
	}
}

void	calcul_data(const std::string &file)
{
	std::fstream	fd;
	std::string		sub;

	fd.open(file.c_str(), std::fstream::in);
	if (fd.fail())
	{
		std::cerr << "error with input file" << std::endl;
		std::exit(2);
	}
	std::getline(fd, sub);
	if (sub != "date | value")
	{
		std::cerr << "error in input file" << std::endl;
		std::exit(2);
	}
	loop_file(fd, sub);
}

int main(int argc, char *argv[])
{
	BitcoinExchange::Date b = BitcoinExchange::Date::extract_date("2012-12-04");
	std::map<BitcoinExchange::Date, float>::iterator c = BitcoinExchange::DB.begin();
	while(c != BitcoinExchange::DB.end())
	{
		std::cout << c->first << " : " << c->second << std::endl;
		c++;
	}
	if (argc != 2)
	{
		std::cerr << "wrong number of arguments" << std::endl;
		return (2);
	}
	calcul_data(argv[1]);
}