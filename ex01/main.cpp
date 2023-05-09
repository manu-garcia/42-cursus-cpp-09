
#include <iostream>

#include "RPN.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: ./RPN expression" << std::endl;
        std::cout << "Example: ./RPN '1 + 1'" << std::endl;
        return 1;
    }

    RPN rpn;

    rpn.reversePolishNotation(argv[1]);

    return 0;
}
