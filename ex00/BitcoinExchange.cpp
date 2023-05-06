#include "BitcoinExchange.hpp"

#include <fstream>
#include <sstream>

#define DB_FILE_PATH "data.csv"

///////////////////////////////////////////////////////////////////////////////
// Constructors / Destructor
///////////////////////////////////////////////////////////////////////////////

BitcoinExchange::BitcoinExchange() : dbLength(0)
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &bitcoinExchange)
{
	*this = bitcoinExchange;
}

BitcoinExchange::~BitcoinExchange()
{
}

///////////////////////////////////////////////////////////////////////////////
// Operators
///////////////////////////////////////////////////////////////////////////////

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &bitcoinExchange)
{
	clearDB();
	db = bitcoinExchange.db;
	dbLength = bitcoinExchange.dbLength;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Member functions
///////////////////////////////////////////////////////////////////////////////

void BitcoinExchange::clearDB()
{
	db.clear();
	dbLength = 0;
}

bool BitcoinExchange::loadDB(std::string filePath)
{
	clearDB();

	std::ifstream fileStream(filePath);
	if (!fileStream)
	{
		std::cerr << "Error: Error reading database file: " << filePath << std::endl;
		return false;
	}

	std::string line;
	if (!std::getline(fileStream, line))
	{
		std::cerr << "Error: Error reading empty database file: " << filePath << std::endl;
		return false;
	}

	while (std::getline(fileStream, line))
	{
		DBPair *linePair = lineToPair(line, ',');
		if (!linePair)
		{
			clearDB();
			std::cerr << "Error: Error reading invalid format database file: " << filePath << std::endl;
			return false;
		}

		db.insert(*linePair);
		delete linePair;
		dbLength++;
	}

	if (!dbLength)
	{
		std::cerr << "Error: Error reading empty database file: " << filePath << std::endl;
		return false;
	}

	return true;
}

DBPair *BitcoinExchange::lineToPair(std::string line, char delimiter)
{
	std::istringstream iss(line);
	std::string date;
	double value;

	if (!std::getline(iss, date, delimiter))
	{
		std::cerr << "Error: Bad input. Failed to read date from line" << std::endl;
		return NULL;
	}

	if (!(iss >> value))
	{
		std::cerr << "Error:  Bad input. Failed to read value from line" << std::endl;
		return NULL;
	}

	iss >> std::ws;
	if (!iss.eof())
	{
		std::cerr << "Error:  Bad input. Extra characters found in line \"" << line << "\"\n";
		return NULL;
	}

	// Trims spaces
	date.erase(remove_if(date.begin(), date.end(), isspace), date.end());

	return new DBPair(date, value);
}

DBPair BitcoinExchange::findExchangeRate(std::string date)
{
	DBMap::iterator it = db.find(date);
	if (it != db.end())
	{
		return *it;
	}
	else
	{
		it = db.upper_bound(date);
		if (it == db.begin())
		{
			// date is before the beginning of the map
			throw std::out_of_range("Date is before the beginning of the exchange rate database.");
		}
		else
		{
			// date is in between two elements in the map
			--it;
			return *it;
		}
	}
}

bool BitcoinExchange::displayBitcoinExchange(char *inputDBFilePath)
{
	if (!loadDB(DB_FILE_PATH))
	{
		return false;
	}

	std::ifstream fileStream(inputDBFilePath);
	std::string line;
	std::string date;
	double value;

	if (!fileStream || !std::getline(fileStream, line))
		return false;

	if (line != "date | value")
		return false;

	while (std::getline(fileStream, line))
	{
		DBPair *linePair = lineToPair(line, '|');
		if (!linePair)
			continue;

		date = linePair->first;
		value = linePair->second;
		delete linePair;

		if (!isValidDate(date))
		{
			std::cout << "Error: bad input (Date) => " << date << std::endl;
			continue;
		}

		if (!isValidValue(value))
		{
			continue;
		}

		try
		{
			DBPair foundonDatePair = findExchangeRate(date);
			std::cout << date << " => " << value << " = " << foundonDatePair.second * value << std::endl;
		}
		catch (std::out_of_range &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	return true;
}

bool BitcoinExchange::isValidValue(double value)
{
	if (value < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return false;
	}
	if (value > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return false;
	}

	return true;
}

bool BitcoinExchange::isValidDate(std::string date)
{
	std::tm time = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	std::istringstream ss(date);

	ss >> std::get_time(&time, "%Y-%m-%d");

	return ss.eof() && mktime(&time) != -1;
}
