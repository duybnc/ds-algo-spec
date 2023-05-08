#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n)
{
    vector<int> summands;
    int max = 0;
    while (n > 0)
    {
        if (n >max) {
            max += 1;
            summands.push_back(max);
            n -= max;
        } else {
            summands.pop_back();
            max += n;
            summands.push_back(max);
            n -= n;
        }
    }
    return summands;
}

int main()
{
    int n;
    std::cin >> n;
    vector<int> summands = optimal_summands(n);
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i)
    {
        std::cout << summands[i] << ' ';
    }
}
