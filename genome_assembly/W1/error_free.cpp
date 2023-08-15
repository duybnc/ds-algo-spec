//
// Created by Duy Bui on 8/14/2023.
//
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct GenomeAssembler {
    const int L = 100;
    int find_bigger_overlap(string &s1, string &s2, int prev_overlap_size) {
      int res = -1;
      for (int i = L - 1; i <prev_overlap_size; i--) {
        if(s2.rfind(s1.substr(L - i), 0) == 0) {
          res = i;
          break;
        }
      }
      return res;
    }
    vector<string> data;
    GenomeAssembler(vector<string> &r): data(r) {};
public:
    string solve() {
      int size = data.size();
      vector<pair<int, int>> next_s (size, make_pair(0,-1));
      for (size_t i =0; i <size; i++) {
        string s1 = data[i];
        for (size_t j = i +1 ; j <size; j++) {
          string s2 = data[j];
          int prev_overlap_size_i = next_s[i].first;
          int prev_overlap_size_j = next_s[j].first;
          int overlap_size_i = find_bigger_overlap(s1, s2, prev_overlap_size_i);
          int overlap_size_j = find_bigger_overlap(s2, s1, prev_overlap_size_j);
          if (prev_overlap_size_i != -1)
            next_s[i] = {overlap_size_i, j};
          if (prev_overlap_size_j != -1)
            next_s[j] = {overlap_size_j, i};
        }
      }
      vector<string> str_parts;
      str_parts.push_back(data[0]);
      int overlap_size = next_s[0].first, cur = next_s[0].second;
      while (cur != 0) {
        str_parts.push_back(data[cur].substr(overlap_size));
        overlap_size = next_s[cur].first, cur = next_s[cur].second;
      }
      string s;
      for (const auto & str_part : str_parts)
        s += str_part;
      //truncate identical symbols
      return s.substr(0, s.length()-overlap_size);
    }
};
int main() {
  ios::sync_with_stdio(false);
  const int rows = 1618;
  vector<string> r(rows);
  string s;

  while( cin >> s) {
    if (s!= r.back())
      r.emplace_back(s);
  }
  string ans = GenomeAssembler(r).solve();
  cout << ans << endl;
  return 0;
}