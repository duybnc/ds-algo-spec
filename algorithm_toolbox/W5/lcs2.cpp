//
// Created by Duy Bui on 5/13/2023.
//
#include <iostream>
#include <vector>

using std::vector;
using namespace std;

int lcs2(vector<int> &a, vector<int> &b) {
    //check slides for implement
    int D[a.size()+1][b.size()+1];
    for (int i=0; i<= a.size(); i++) {
        for (int j=0; j <= b.size(); j++) {
            D[i][j] = 0;
        }
    }

    for (int i=1; i<= a.size(); i++) {
        for (int j=1; j <= b.size(); j++) {
            if(a[i-1] == b[j-1]) {
                D[i][j] = 1 + D[i-1][j-1];
            } else {
                D[i][j] = max(D[i-1][j], D[i][j-1]);
            }
        }
    }
    return D[a.size()][b.size()];
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    size_t m;
    std::cin >> m;
    vector<int> b(m);
    for (size_t i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    std::cout << lcs2(a, b) << std::endl;
}
