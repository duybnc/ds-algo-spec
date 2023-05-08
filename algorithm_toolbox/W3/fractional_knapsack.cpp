#include <iostream>
#include <vector>
#include <iomanip>

using std::vector;

int get_max(vector<int> weights, vector<int> values) {
    int maxIndex = 0;
    double max = 0;
    for (int i = 0; i < weights.size(); i++) {
        double temp = (double) values[i] / weights[i];
        if (temp > max)
        {
            max = temp;
            maxIndex = i;
        }
    }
    return maxIndex;
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values)
{
    double value = 0.0;

    if (capacity ==0 || weights.empty()) return value;
    int index = get_max(weights, values);
    int amount = std::min(weights[index], capacity);
    value = amount * (double) values[index] / weights[index];
    weights.erase(weights.begin() + index);
    values.erase(values.begin() + index);
    capacity -= amount;
    return static_cast<double> (value + get_optimal_value(capacity, weights, values));
}

int main()
{
    int n;
    int capacity;
    std::cin >> n >> capacity;
    vector<int> values(n);
    vector<int> weights(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> values[i] >> weights[i];
    }

    double optimal_value = get_optimal_value(capacity, weights, values);

    std::cout << std::fixed;
    std::cout << std::setprecision(4) << optimal_value << std::endl;
    // std::cout.precision(10);
    // std::cout << optimal_value << std::endl;
    return 0;
}
