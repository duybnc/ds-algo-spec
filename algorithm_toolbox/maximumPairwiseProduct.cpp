#include <iostream>
#include <vector>
#include <cstdlib>

using std::cout;
using std::vector;

long long MaxPairwiseProduct(const std::vector<int> &numbers)
{
    int n = numbers.size();
    int one = -1;
    int two = -1;
    int i = 0;
    while (i < n) {
        int temp = numbers[i];
        if (temp >= one) {
            two = one;
            one = temp;
        } else if (temp >= two ) {
            two = temp;
        }
        i++;
    }

    return ((long long) one * two);
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> numbers[i];
    }

    std::cout << MaxPairwiseProduct(numbers) << "\n";
    return 0;
}
