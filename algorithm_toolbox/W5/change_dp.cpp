//
// Created by Duy Bui on 5/11/2023.
//
#include <iostream>
#include <vector>
#include <limits>
using std::vector;
using std::numeric_limits;
using std::min;
int get_change(int m) {
    vector<int> changes(m+1);
    int a, b, c;
    for (int i =0; i<=m; i++) {
        a = b = c = numeric_limits<int>::max();
        // check slide for implement
        if(i-1 >= 0) {
            a = 1 + changes[i-1];
            if(i-3 >= 0) {
                b = 1 + changes[i-3];
                if(i-4 >= 0) {
                    c = 1 + changes[i-4];
                }
            }
            changes[i] = min(a, min(b,c));
        } else {
            changes[i] = 0;
        }

    }
    return changes[m];
}

int main() {
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
