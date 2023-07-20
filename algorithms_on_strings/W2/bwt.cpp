#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
  string result = "";

  // write your code here
  vector<string> s(text.size());
  for (size_t i = 0; i < s.size(); i++) {
    s[i] = text.substr(i) + text.substr(0, i);
  }

  sort(s.begin(), s.end());

  for (size_t i = 0; i < s.size(); i++) {
    result += s[i][s.size() - 1];
  }
  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}