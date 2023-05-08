//
// Created by Duy Bui on 5/7/2023.
//
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using std::vector;

int get_majority_element(vector<int> &a, int left, int right) {
    if (left == right) return -1;
    if (left + 1 == right) return a[left];
    std::map<int, int> b;
    for(size_t i = 0; i < a.size(); ++i) {
        if(b[a[i]] == 0) {
            b[a[i]] =1;
        } else {
            b[a[i]] += 1;
            if (b[a[i]] > ((int) a.size()/2)) {
                return a[i];
            }
        }
    }
    return -1;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
