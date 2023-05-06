#include <iostream>

#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return (1);
    }

    BitcoinExchange btc;
    if (!btc.displayBitcoinExchange(argv[1]))
    {
        std::cerr << "Error: Error displaying Bitcoin Exchange for the " << argv[1] << " file." << std::endl;
        return (3);
    }

    return (0);
}
