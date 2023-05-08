#include <iostream>
#include <vector>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to)
{
    from = from % 60;
    to = to % 60;
    long long sum = 0;

    long long previous = 0;
    long long current = 1;
    if ( (from == 0 && to != 0) || from == 1 || to == 1)
        sum = 1;

    if (to < from)
        to += 60;

    for (long long i = 2; i <= to; ++i)
    {
        long long tmp = previous;
        previous = current;
        current = (tmp + current) % 10;

        if (i >= from)
        {
            sum += current;
        }
    }

    return sum % 10;
}

int main()
{
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
}
