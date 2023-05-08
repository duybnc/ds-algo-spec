#include <iostream>
#include <vector>

int get_fibonacci_last_digit_naive(int n)
{
    std::vector<int> a;
    if (n <= 1)
    {
        return n;
    }
    a.push_back(0);
    a.push_back(1);
    for (int i = 2; i <= n; i++)
    {
        int temp = (a[i - 1] + a[i - 2]) % 10;
        a.push_back(temp);
    }
    return a[n];
}

int main()
{
    int n;
    std::cin >> n;
    int c = get_fibonacci_last_digit_naive(n);
    std::cout << c << '\n';
}
