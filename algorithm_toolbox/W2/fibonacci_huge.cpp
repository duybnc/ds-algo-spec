#include <iostream>
#include <vector>

long long get_fibonacci_huge_naive(long long n, long long m)
{
    std::vector<long long> a;
    if (n <= 1)
        return n;
    a.push_back(0);
    a.push_back(1);
    long long previous = 0;
    long long current = 1;

    for (long long i = 0; i <n ; ++i)
    {
        long long temp = previous;
        previous = current % m;
        current = (temp + current) % m;
        a.push_back(current);
        if (temp == 1 && previous == 0)
        {
            int index = n % (i + 1);
            return a[index];
        }
    }

    return a[n];
}

int main()
{
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_naive(n, m) << '\n';
}
