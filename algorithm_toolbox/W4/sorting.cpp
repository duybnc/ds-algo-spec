//
// Created by Duy Bui on 5/7/2023.
//
#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

std::pair<int, int> partition2(vector<int> &a, int l, int r) {
    int x = a[l];
    int j = l;
    int k = r;
    for (int i = l; i <= r; i++) {
        if (a[i] < x) {
            swap(a[i], a[j]);
            j++;
        }
    }
    for (int i =r; i>=l; i--) {
        if (a[i] >x) {
            swap(a[i], a[k]);
            k--;
        }
    }
    return std::make_pair(j, k);
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
    if (l >= r) {
        return;
    }

    int k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);
    auto m = partition2(a, l, r);

    randomized_quick_sort(a, l, m.first - 1);
    randomized_quick_sort(a, m.second + 1, r);
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    randomized_quick_sort(a, 0, a.size() - 1);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
}
