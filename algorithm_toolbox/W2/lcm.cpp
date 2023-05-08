#include <iostream>
int gcd_naive(int a, int b)
{
    if (b == 0)
        return a;
    int c = a % b;
    return gcd_naive(b, c);
}

long long lcm_naive(int a, int b)
{
    int gcd = 1;
    if (a >= b){
        gcd = gcd_naive(a, b);
    } else {
        gcd = gcd_naive(b, a);
    }

    return (long long)a * b / gcd;
}

int main()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << lcm_naive(a, b) << std::endl;
    return 0;
}
