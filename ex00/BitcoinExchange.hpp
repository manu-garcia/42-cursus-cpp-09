#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>

typedef std::map<std::string, double> DBMap;
typedef std::pair<std::string, double> DBPair;

class BitcoinExchange
{
private:
	DBMap db;
	unsigned int dbLength;

	void clearDB();
	bool loadDB(std::string filePath);
	DBPair *lineToPair(std::string line, char delimiter);
	DBPair findExchangeRate(std::string date);
	bool isValidDate(std::string date);
	bool isValidValue(double value);

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &bitcoinExchange);
	~BitcoinExchange();

	BitcoinExchange &operator=(const BitcoinExchange &bitcoinExchange);

	bool displayBitcoinExchange(char *filePath);
};

#endif
