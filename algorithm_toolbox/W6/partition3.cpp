//
// Created by Duy Bui on 5/19/2023.
//
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using std::vector;
using namespace std;
int target;
vector<int> p(3, 0);
bool p_search(vector<int> &A, int index) {
    if (index >= A.size()) return true;
    for (size_t i =0; i <p.size(); i ++) {
        if(p[i] + A[index] <= target) {
            p[i] += A[index];
            if (p_search(A ,index+1)) return true;
            p[i] -= A[index];
        }
    }
    return false;
}

bool partition3(vector<int> &A) {
    int sum = std::accumulate(A.begin(), A.end(), 0);
    if (sum %3 !=0 || A.size() <3 || *max_element(A.begin(), A.end()) > sum/3) return false;
    sort(A.begin(), A.end(), greater<int>());
    target = sum /3;
    return p_search(A, 0);
}

int main() {
    int n;
    std::cin >> n;
    vector<int> A(n);
    for (size_t i = 0; i < A.size(); ++i) {
        std::cin >> A[i];
    }
    std::cout << partition3(A) << '\n';
}
