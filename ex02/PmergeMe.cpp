#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
    parse_args(argc, argv);
}

void PmergeMe::run()
{
    std::cout << "Before: ";
    print_numbers(numbers);

    clock_t start_time_vector = clock();

    sort_using_vector();

    double elapsed_time_vector = (clock() - start_time_vector) * 1e6 / CLOCKS_PER_SEC;

    std::cout << "After: ";
    print_numbers(sorted_numbers);

    std::cout << "Time to process a range of " << numbers.size() << " elements with vector: " << elapsed_time_vector << " us" << std::endl;

    clock_t start_time_deque = clock();

    sort_using_deque();

    double elapsed_time_deque = (clock() - start_time_deque) * 1e6 / CLOCKS_PER_SEC;

    std::cout << "After: ";
    print_deque(deque_sorted_numbers);

    std::cout << "Time to process a range of " << numbers.size() << " elements with deque: " << elapsed_time_deque << " us" << std::endl;
}

void PmergeMe::parse_args(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: no arguments provided" << std::endl;
        exit(1);
    }

    for (int i = 1; i < argc; i++)
    {
        std::istringstream iss(argv[i]);
        int num;
        if (iss >> num)
        {
            if (num > 0)
            {
                numbers.push_back(num);
            }
        }
        else
        {
            std::cerr << "Error: invalid argument: " << argv[i] << std::endl;
            exit(1);
        }
    }
}

void PmergeMe::print_numbers(std::vector<int> &numbersVector)
{
    for (std::vector<int>::iterator it = numbersVector.begin(); it != numbersVector.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::print_deque(std::deque<int> &numbersDeque)
{
    for (std::deque<int>::iterator it = numbersDeque.begin(); it != numbersDeque.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::sort_using_vector()
{
    sorted_numbers = numbers;
    merge_sort(sorted_numbers);
}

void PmergeMe::sort_using_deque()
{
    deque_numbers = std::deque<int>(numbers.begin(), numbers.end());
    merge_sort(deque_numbers);
    deque_sorted_numbers = deque_numbers;
}

void PmergeMe::merge_sort(std::vector<int> &vec)
{
    if (vec.size() <= 1)
    {
        return;
    }

    int middle = vec.size() / 2;
    std::vector<int> left(vec.begin(), vec.begin() + middle);
    std::vector<int> right(vec.begin() + middle, vec.end());

    merge_sort(left);
    merge_sort(right);

    merge(left, right, vec);
}

void PmergeMe::merge_sort(std::deque<int> &deq)
{
    if (deq.size() <= 1)
    {
        return;
    }

    int middle = deq.size() / 2;
    std::deque<int> left(deq.begin(), deq.begin() + middle);
    std::deque<int> right(deq.begin() + middle, deq.end());

    merge_sort(left);
    merge_sort(right);

    merge(left, right, deq);
}

void PmergeMe::merge(std::vector<int> &left, std::vector<int> &right, std::vector<int> &result)
{
    result.clear();
    unsigned long i = 0, j = 0;
    while (i < left.size() && j < right.size())
    {
        if (left[i] <= right[j])
        {
            result.push_back(left[i]);
            i++;
        }
        else
        {
            result.push_back(right[j]);
            j++;
        }
    }
    while (i < left.size())
    {
        result.push_back(left[i]);
        i++;
    }
    while (j < right.size())
    {
        result.push_back(right[j]);
        j++;
    }
}

void PmergeMe::merge(std::deque<int> &left, std::deque<int> &right, std::deque<int> &result)
{
    result.clear();
    while (!left.empty() && !right.empty())
    {
        if (left.front() <= right.front())
        {
            result.push_back(left.front());
            left.pop_front();
        }
        else
        {
            result.push_back(right.front());
            right.pop_front();
        }
    }

    while (!left.empty())
    {
        result.push_back(left.front());
        left.pop_front();
    }

    while (!right.empty())
    {
        result.push_back(right.front());
        right.pop_front();
    }
}
