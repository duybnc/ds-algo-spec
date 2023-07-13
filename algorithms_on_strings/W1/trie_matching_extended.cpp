#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}
vector<Node> build_trie(const vector<string> &patterns) {
  vector<Node> trie(1);
  for (size_t i = 0; i < patterns.size(); i++) {
    const string &pattern = patterns[i];
    int current = 0;
    for (size_t j = 0; j < pattern.size(); j++) {
      char x = pattern[j];
      int index  = letterToIndex(x);
      int y = trie[current].next[index ];
      // old leaf
      if (y != -1) {
        current = y;
        // new leaf
      } else {
        y = trie.size();
        trie.push_back(Node());
        trie[current].next[index] = y;
        current = y;
      }
    }
    trie[current].patternEnd = true;
  }
  return trie;
}
vector <int> solve (string text, int n, vector <string> patterns)
{
	vector <int> result;

	// write your code here
  vector<Node> trie = build_trie(patterns);
  for (size_t i = 0; i < text.size(); i++) {
    int index = letterToIndex(text[i]);
    int x = 0;
    if(trie[x].next[index] != -1) {
      bool found = true;
      for (size_t j = i; !trie[x].patternEnd; j++) {
        if (j >= text.size()) {
          found = false;
          break;
        }
        index = letterToIndex(text[j]);
        if (trie[x].next[index] != -1) x = trie[x].next[index];
        else {
          found = false;
          break;
        }
      }
      if(found) result.push_back(i);
    }
  }
	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
