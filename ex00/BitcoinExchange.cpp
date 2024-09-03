#include <fstream>
#include <cstdlib>
#include "BitcoinExchange.hpp"

std::map<BitcoinExchange::Date, float>  make_database();

std::map<BitcoinExchange::Date, float> BitcoinExchange::DB = make_database();

BitcoinExchange::Date::Date()
{

}

BitcoinExchange::Date::Date(int year, int month, int day) : year(year), month(month), day(day)
{

}

BitcoinExchange::Date::Date(const Date &copy) : year(copy.year), month(copy.month), day(copy.day)
{

}

BitcoinExchange::Date::~Date()
{

}

int	BitcoinExchange::Date::get_year() const
{
	return (year);
}

int	BitcoinExchange::Date::get_month() const
{
	return (month);
}

int	BitcoinExchange::Date::get_day() const
{
	return (day);
}

void	BitcoinExchange::Date::operator=(const Date &copy)
{
	year = copy.year;
	month = copy.month;
	day = copy.day;
}

int	BitcoinExchange::Date::is_year(const std::string &year)
{
	if (year.find_first_not_of("0123456789") != std::string::npos)
		return (0);
	return (1);
}

int BitcoinExchange::Date::is_month(const std::string &month)
{
	int	m = std::atoi(month.c_str());

	if (month.find_first_not_of("0123456789") != std::string::npos ||
		m > 12 || m < 1)
		return (0);
	return (1);
}

int BitcoinExchange::Date::is_day(const std::string &day)
{
	int	m = std::atoi(day.c_str());

	if (day.find_first_not_of("0123456789") != std::string::npos ||
		m > 31 || m < 1)
		return (0);
	return (1);
}

int	BitcoinExchange::Date::check_date(const std::string &date)
{
	std::string	sub;

	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (0);
	sub = date.substr(0, 4);
	// std::cout << sub << std::endl;
	if (!is_year(sub))
		return (0);
	sub = date.substr(5, 2);
	// std::cout << sub << std::endl;
	if (!is_month(sub))
		return (0);
	sub = date.substr(8, 2);
	// std::cout << sub << std::endl;
	if (!is_day(sub))
		return (0);
	return (1);
}

BitcoinExchange::Date	BitcoinExchange::Date::extract_date(const std::string &date)
{
	if (!check_date(date))
		throw(std::exception());
	return (Date(atoi(date.substr(0, 4).c_str()),
				atoi(date.substr(5, 2).c_str()),
				atoi(date.substr(8, 2).c_str())));
}

bool	BitcoinExchange::Date::operator<(const Date &a) const
{
	if (year < a.year)
		return (1);
	else if (year == a.year)
	{
		if (month < a.month)
			return (1);
		else if (month == a.month && day < a.day)
			return (1);
	}
	return (0);
}

bool	BitcoinExchange::Date::operator==(const Date &a) const
{
	if (year == a.year && month == a.month && day == a.day)
		return (1);
	return (0);
}

std::ostream &operator<<(std::ostream &a, const BitcoinExchange::Date &b)
{
	std::cout << b.get_year() << "-";
	if (b.get_month() < 10)
		std::cout << 0;
	std::cout << b.get_month() << "-";
	if (b.get_day() < 10)
		std::cout << 0;
	std::cout << b.get_day();
	return (a);
}

static bool	is_float(const std::string &sub)
{
	if (sub.find_first_not_of("0123456789.") != std::string::npos)
		return (0);
	std::strtod(sub.c_str(), 0);
	if (errno == ERANGE)
		return (0);
	return (1);
}

static void	parse_db(std::fstream &data, std::map<BitcoinExchange::Date, float> &ret)
{
	std::string	line;
	int	i = 2;

	while (std::getline(data, line))
	{
		if (line.find(',') == std::string::npos)
		{
			std::cerr << "Error in database(format)::" << i <<  std::endl;
			std::exit(5);
		}
		std::string sub = line.substr(0, line.find(','));
		std::string sub2 = line.substr(line.find(',') + 1);
		if (!is_float(sub2))
		{
			std::cerr << "Error in database(float)::" << i <<  std::endl;
			std::exit(3);
		}
		// std::cout << sub << std::endl << sub2 << std::endl;
		try
		{
			ret.insert(std::Pair<std::vector><BitcoinExchange::Date, float>(BitcoinExchange::Date::extract_date(sub), std::atof(sub2.c_str())));
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << "::" << i <<std::endl;
			std::exit(4);
		}
		i++;
	}
}

std::map<BitcoinExchange::Date, float> make_database()
{
	std::map<BitcoinExchange::Date, float>	ret;
	std::fstream			data;
	std::string				line;

	data.open("data.csv", std::fstream::in);
	if ((data.rdstate() & std::fstream::failbit) != 0)
	{
		std::cerr << "Error opening data.csv" << std::endl;
		std::exit(1);
	}
	std::getline(data, line);
	if (line != "date,exchange_rate")
	{
		std::cerr << "Error in database" << std::endl;
		std::exit(2);
	}
	parse_db(data, ret);
	return (ret);
}