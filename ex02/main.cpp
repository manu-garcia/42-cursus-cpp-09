
#include <iostream>
#include <vector>
#include <sstream>

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    // Create an instance of PmergeMe
    PmergeMe pmerge(argc, argv);

    // Run the sorting and timing code
    pmerge.run();

    return 0;
}
