#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t(1);
  // write your code here
  for (size_t i = 0; i < patterns.size(); i++) {
    string &pattern = patterns[i];
    int current = 0;
    for (size_t j = 0; j < pattern.size(); j++) {
      char x = pattern[j];
      auto it = t[current].find(x);
      // old leaf
      if (it != t[current].end()) {
        current = it->second;
      // new leaf
      } else {
        int new_node = t.size();
        t.push_back(edges());
        t[current].insert(std::make_pair(x, new_node));
        current = new_node;
      }
    }
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}