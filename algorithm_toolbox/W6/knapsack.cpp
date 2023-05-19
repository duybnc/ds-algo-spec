//
// Created by Duy Bui on 5/19/2023.
//
#include <iostream>
#include <vector>

using std::vector;
using std::max;

int optimal_weight(int W, const vector<int> &w) {
    vector<vector <int>> T (w.size() +1, vector<int> (W +1));
    for (size_t i =0; i <= W; i++) T[0][i] = 0;
    for (size_t i =0; i <= w.size(); i++) T[i][0] = 0;
    for (int i = 1; i <= w.size(); i++ ){
        for(int u=1; u<= W; u++) {
            T[i][u] = T[i-1][u];
            if (u >= w[i-1]) {
                T[i][u] = max(T[i-1][u], T[i-1][u - w[i-1]] + w[i-1]);
            }
        }
    }
    return T[w.size()][W];
}

int main() {
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';
}
