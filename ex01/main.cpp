
#include <iostream>

#include "RPN.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: ./RPN expression" << std::endl;
        std::cout << "Example: ./RPN '1 1 +'" << std::endl;
        return 1;
    }

    RPN rpn;

    rpn.reversePolishNotation(argv[1]);

    return 0;
}

// int main(int argc, char *argv[])
// {
//     (void)argv;
//     (void)argc;

//     RPN rpn;

//     assert(rpn.reversePolishNotation("2 3 +") == 5);
//     assert(rpn.reversePolishNotation("4 5 +") == 9);
//     assert(rpn.reversePolishNotation("5 3 -") == 2);
//     assert(rpn.reversePolishNotation("6 2 /") == 3);
//     assert(rpn.reversePolishNotation("3 4 *") == 12);
//     assert(rpn.reversePolishNotation("8 2 / 3 +") == 7);
//     assert(rpn.reversePolishNotation("7 2 * 4 +") == 18);
//     assert(rpn.reversePolishNotation("9 3 - 2 +") == 8);
//     assert(rpn.reversePolishNotation("5 2 * 1 +") == 11);
//     assert(rpn.reversePolishNotation("3 2 / 4 +") == 5);
//     assert(rpn.reversePolishNotation("2 3 4 + +") == 9);
//     assert(rpn.reversePolishNotation("4 5 2 - -") == 1);
//     assert(rpn.reversePolishNotation("5 3 2 * *") == 30);
//     assert(rpn.reversePolishNotation("3 4 5 + -") == -6);
//     assert(rpn.reversePolishNotation("8 2 4 * /") == 1);
//     assert(rpn.reversePolishNotation("7 2 4 + -") == 1);
//     assert(rpn.reversePolishNotation("9 3 2 - +") == 10);
//     assert(rpn.reversePolishNotation("5 2 1 * +") == 7);
//     assert(rpn.reversePolishNotation("3 4 2 / +") == 5);
//     assert(rpn.reversePolishNotation("1 1 1 + -") == -1);
//     assert(rpn.reversePolishNotation("2 3 4 - +") == 1);
//     assert(rpn.reversePolishNotation("4 5 2 + -") == -3);
//     assert(rpn.reversePolishNotation("5 3 2 * +") == 11);
//     assert(rpn.reversePolishNotation("6 2 3 * /") == 1);
//     assert(rpn.reversePolishNotation("3 4 5 - +") == 2);
//     assert(rpn.reversePolishNotation("8 4 2 / *") == 16);
//     assert(rpn.reversePolishNotation("7 2 4 - +") == 5);
//     assert(rpn.reversePolishNotation("9 3 2 + -") == 4);
//     assert(rpn.reversePolishNotation("5 2 1 + *") == 15);
//     return 0;
// }
