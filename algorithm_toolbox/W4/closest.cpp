//
// Created by Duy Bui on 5/8/2023.
//
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using std::vector;
using std::string;
using std::pair;
using std::min;
using std::make_pair;

double distance(pair<int,int> p1, pair<int, int> p2) {
    return (double) sqrt((p1.first - p2.first) *(p1.first - p2.first) + (p1.second - p2.second) *(p1.second - p2.second));
}

bool compareX(pair<int,int> p1, pair<int, int> p2) {
    return (p1.first == p2.first) ? (p1.second < p2.second) : (p1.first<p2.first);
}

bool compareY(pair<int,int> p1, pair<int, int> p2) {
    return (p1.second == p2.second) ? (p1.first < p2.first) : (p1.second<p2.second);
}

void compare(vector<pair<int, int>>& points, int l, int r) {
    if (l >= r) return;

    int mid = l + (r-l)/2;
    int i = l, j = mid + 1;
    vector<pair<int, int>> vec;
    vec.reserve(r - l + 1);

    while (i <= mid and j <= r) {
        if (compareY(points[i], points[j])) {
            vec.emplace_back(points[i].first, points[i].second);
            i++;
        } else {
            vec.emplace_back(points[j].first, points[j].second);
            j++;
        }
    }
    while (i <= mid) {
        vec.emplace_back(points[i].first, points[i].second);
        i++;
    }
    while (j <= r) {
        vec.emplace_back(points[j].first, points[j].second);
        j++;
    }

    for (size_t k = 0; k < vec.size(); k++) { points[l + k] = vec.at(k); }
}

double minimal_distance(vector<pair<int,int>> points, int l, int r) {
    if (l >= r) return std::numeric_limits<double>::max();
    if (r - l == 1) {
        if (not compareY(points[l], points[r])) {
            swap(points[l], points[r]);
        }
        return distance(points[r], points[l]);
    }
    int m = l + (r-l)/2;
    pair<int, int> midPoint = points[m];
    double d = min(minimal_distance(points, l, m), minimal_distance(points, m+1, r));
    compare(points, l, r);
    vector<pair<int,int>> middlePoints;
    for (int i = l; i <= r; i++) {
        if (abs(points[i].first - midPoint.first) <= d) {
            middlePoints.emplace_back(points[i].first, points[i].second);
        }
    }
   // check statements file for induction
    for (long long i = 0; i < middlePoints.size() - 1; i++) {
        for (long long j = i + 1; j < middlePoints.size() and j - i < 8; j++) {
            d = min(d, distance(middlePoints[i], middlePoints[j]));
        }
    }
    return d;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> x(n);
    vector<int> y(n);
    vector<pair<int,int>> points;
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
        points.emplace_back(x[i], y[i]);
    }
    sort(points.begin(), points.end(), &compareX);
    std::cout << std::fixed;
    std::cout << std::setprecision(9) << minimal_distance(points, 0, points.size()-1) << "\n";
}
