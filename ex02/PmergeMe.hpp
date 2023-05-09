#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <ctime>

class PmergeMe
{
public:
    PmergeMe(int argc, char **argv);

    void run();

private:
    std::vector<int> numbers;
    std::vector<int> sorted_numbers;
    std::deque<int> deque_numbers;
    std::deque<int> deque_sorted_numbers;

    void parse_args(int argc, char **argv);
    void print_numbers(std::vector<int> &numbers);
    void print_deque(std::deque<int> &numbers);

    void sort_using_vector();
    void sort_using_deque();

    void merge_sort(std::vector<int> &vec);
    void merge_sort(std::deque<int> &deq);

    void merge(std::vector<int> &left, std::vector<int> &right, std::vector<int> &result);
    void merge(std::deque<int> &left, std::deque<int> &right, std::deque<int> &result);
};

#endif
