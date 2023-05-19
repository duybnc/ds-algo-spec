//
// Created by Duy Bui on 5/19/2023.
//
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <limits>

using std::vector;
using std::string;
using std::max;
using std::min;
using std::pair;
using std::make_pair;
using std::numeric_limits;

long long eval(long long a, long long b, char op) {
    if (op == '*') {
        return a * b;
    } else if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else {
        assert(0);
    }
}

long long get_maximum_value(const string &exp) {
    size_t n = (exp.size() +1) /2;
    vector<pair<long long, long long>> ans(n*n);
    auto array_element = [&ans, n] (long long i, long long j) { return ans[n*i +j];};
    auto set_element = [&ans, n] (long long i, long long j, pair<long long, long long> value) { return ans[n*i +j] = value;};
    auto digit = [&exp](long long i) { return exp[2 * i] - '0'; };
    auto op = [&exp](long long i) { return exp[2 * i +1]; };
    for (size_t i = 0; i < n; i++) {
        set_element(i, i, make_pair(digit(i), digit(i)));
    }
    long long temp_min, temp_max;
    long long a, b, c, d;
    for(size_t i =1; i <n; i++) {
        for(size_t j =i; j <n; j++) {
            temp_min =  numeric_limits<long long>::max();
            temp_max =  numeric_limits<long long>::min();
            for (size_t k = j - i; k < j; k++) {
                a = eval(array_element(j-i, k).first,  array_element(k+1, j).first, op(k));
                b = eval(array_element(j-i, k).second,  array_element(k+1, j).second, op(k));
                c = eval(array_element(j-i, k).first,  array_element(k+1, j).second, op(k));
                d = eval(array_element(j-i, k).second,  array_element(k+1, j).first, op(k));
                temp_min = min(temp_min, min(min(a, b), min(c,d)));
                temp_max = max(temp_max, max(max(a, b), max(c,d)));
                set_element(j - i, j, make_pair(temp_min, temp_max));
            }
        }
    }
    return array_element(0, exp.size() / 2).second;
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
}
