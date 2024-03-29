//
// Created by Duy Bui on 5/13/2023.
//
#include <iostream>
#include <vector>

using std::vector;
using namespace std;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
    int D[a.size()+1][b.size()+1][c.size()+1];
    for (int i=0; i<= a.size(); i++) {
        for (int j=0; j <= b.size(); j++) {
            for (int l=0; l <= c.size(); l++) {
                D[i][j][l] = 0;
            }
        }
    }
    for (int i = 1; i <= a.size(); i++) {
        for (int j = 1; j <= b.size(); j++) {
            for (int k = 1; k <= c.size(); k++) {
                if (a[i - 1] == b[j - 1] and b[j - 1] == c[k - 1]) {
                    D[i][j][k] = 1 + D[i - 1][j - 1][k - 1];
                } else {
                    D[i][j][k] = max(D[i][j][k - 1],
                                     max(D[i][j - 1][k],
                                         max(D[i - 1][j][k],
                                             max(D[i][j - 1][k - 1],
                                                 max(D[i - 1][j][k - 1],
                                                     max(D[i - 1][j - 1][k],D[i - 1][j - 1][k - 1]))))));
                }
            }
        }
    }
    return D[a.size()][b.size()][c.size()];
}

int main() {
    size_t an;
    std::cin >> an;
    vector<int> a(an);
    for (size_t i = 0; i < an; i++) {
        std::cin >> a[i];
    }
    size_t bn;
    std::cin >> bn;
    vector<int> b(bn);
    for (size_t i = 0; i < bn; i++) {
        std::cin >> b[i];
    }
    size_t cn;
    std::cin >> cn;
    vector<int> c(cn);
    for (size_t i = 0; i < cn; i++) {
        std::cin >> c[i];
    }
    std::cout << lcs3(a, b, c) << std::endl;
}
