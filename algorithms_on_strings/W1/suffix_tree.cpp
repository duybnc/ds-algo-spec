#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

struct Node {
    string sub = "";
    vector<int> chs;
    Node() = default;
    Node(const string &sub, std::initializer_list<int> children) : sub(sub) {
      chs.insert(chs.end(), children);
    }
};

struct SuffixTree {
    vector<Node> nodes;

    SuffixTree(const string &t) {
      nodes.push_back(Node{});
      for (size_t i =0 ; i < t.length(); i++) add_suffix(t.substr(i));
    }

    void add_suffix(const string &s){
      // ukkonen's suffix tree al
      int n = 0;
      size_t i = 0;
      while(i < s.length()) {
        char c = s[i];
        int x = 0;
        int n_c;
        while (true) {
          auto child = nodes[n].chs;
          if (x == child.size()) {
            // add new node
            n_c = nodes.size();
            nodes.push_back(Node(s.substr(i), {}));
            nodes[n].chs.push_back(n_c);
            return;
          }
          n_c = child[x];
          if (nodes[n_c].sub[0] == c) break;
          x++;
        }
        string sub2 = nodes[n_c].sub;
        size_t j =0;
        while (j < sub2.size()) {
          if (s[i+j] != sub2[j]) {
            int m = n_c;
            n_c = nodes.size();
            nodes.push_back(Node(sub2.substr(0, j), {m}));
            nodes[m.sub = sub2.substr(j);
            nodes[n].chs[x] = n_c;
            break;
          }
          j++;
        }
        i += j;
        n = n_c;
      }
    }
};
// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  // Implement this function yourself
  SuffixTree s = SuffixTree(text);
  for (size_t i = 0 ; i <s.nodes.size(); i++) {
    if (s.nodes[i].sub != "") result.push_back(s.nodes[i].sub);
  }
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
