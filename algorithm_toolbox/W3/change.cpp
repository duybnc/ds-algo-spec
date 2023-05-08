#include <iostream>

int get_change(int m)
{
    int mod10 = m % 10;
    int c10 = (m - mod10) / 10;
    int mod5 = mod10 % 5;
    int c5 = (mod10 - mod5) / 5;
    return c10 +c5 +mod5;
}

int main()
{
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
