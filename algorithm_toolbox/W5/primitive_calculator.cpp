//
// Created by Duy Bui on 5/11/2023.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using std::vector;

vector<int> optimal_sequence(int n) {
    vector<int> sequence;
    vector<int> arr(n+1);
    int a, b ,c;
    for (int i= 2; i <= n; i ++) {
        a =  b = c = std::numeric_limits<int>::max();
        if (i -1 >=0) { a = 1 + arr[i-1];}
        if (i % 2 == 0 and i /2 >= 0) { b = 1 + arr[i/2]; }
        if (i % 3 == 0 and i /3 >= 0) { c = 1 + arr[i/3]; }
        arr[i] = std::min(a, std::min(b, c));
    }
    while (n > 1) {
        sequence.push_back(n);
        if (n % 3 == 0 && arr[n/3] + 1 == arr[n]) {
            n /= 3;
        } else if (n % 2 == 0 && arr[n/2] + 1 == arr[n]) {
            n /= 2;
        } else {
            n -= 1;
        }
    }
    sequence.push_back(1);
    std::reverse(sequence.begin(), sequence.end());
    return sequence;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> sequence = optimal_sequence(n);
    std::cout << sequence.size() - 1 << std::endl;
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << " ";
    }
}
