//
// Created by Duy Bui on 5/8/2023.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using std::vector;
using std::pair;
using std::make_pair;

vector<int> fast_count_segments(vector<pair<int,int>> segments, vector<int> points) {
    vector<int> cnt(points.size());
    vector<pair<int,int>> trans;
    std::unordered_map<int, int> ans(points.size());
    for(int i=0; i <segments.size(); i++) {
        trans.push_back(make_pair(segments[i].first, 0));
        trans.push_back(make_pair(segments[i].second, 2));
    }
    for (int i=0; i<points.size(); i++) {
        trans.push_back(make_pair(points[i], 1));
    }
    std::sort(trans.begin(), trans.end(), [](pair<int, int>& a, pair<int, int>& b) {
        if(a.first == b.first) return a.second < b.second;
        else return a.first < b.first;
    });
    int count = 0;
    for (int i = 0; i < trans.size(); i++ ) {
        if (trans[i].second == 0) {
            count ++;
            continue;
        }
        if (trans[i].second == 2) {
            count--;
            continue;
        }
        ans.insert(make_pair(trans[i].first, count));
    }
    for (int i =0; i < points.size(); i++) {
        cnt[i] = ans[points[i]];
    }
    return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < starts.size(); j++) {
            cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
        }
    }
    return cnt;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<int> starts(n), ends(n);
    vector<std::pair<int,int>> segments;
    for (size_t i = 0; i < starts.size(); i++) {
        std::cin >> starts[i] >> ends[i];
        segments.push_back(std::make_pair(starts[i], ends[i]));
    }
    vector<int> points(m);
    for (size_t i = 0; i < points.size(); i++) {
        std::cin >> points[i];
    }
    //use fast_count_segments
//    vector<int> cnt = naive_count_segments(starts, ends, points);
    vector<int> cnt = fast_count_segments(segments, points);
    for (size_t i = 0; i < cnt.size(); i++) {
        std::cout << cnt[i] << ' ';
    }
}
