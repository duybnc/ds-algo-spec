//
// Created by Duy Bui on 8/15/2023.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <stack>

using namespace std;

bool check_degree(const vector<int> &in, const vector<int> &out) {
  assert(in.size() == out.size());
  for (size_t i = 0; i < in.size(); ++i)
    if (in[i] != out[i])
      return false;
  return true;
}

vector<int> make_euler_cycle(vector<vector<int>> graph) {
  // bfs
  stack<int> vertex;
  vector<int> path;
  vertex.push(0);
  int current = 0;

  while (not vertex.empty()) {
    current = vertex.top();
    if (not graph[current].empty()) {
      vertex.push(graph[current].back());
      graph[current].pop_back();
      continue;
    }
    path.push_back(current);
    vertex.pop();
  }

  reverse(path.begin(), path.end());
  path.pop_back();
  return path;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;

  cin >> n >> m;

  vector<vector<int>> graph(n);

  vector<int> in(n), out(n);

  for (int i = 0; i < m; ++i) {
    int from, to;
    cin >> from >> to;
    graph[--from].push_back(--to);
    ++in[to];
    ++out[from];
  }

  if (not check_degree(in, out)) {
    cout << 0 << endl;
    return 0;
  }

  auto cycle = make_euler_cycle(std::move(graph));

  cout << 1 << '\n';
  for (auto v : cycle)
    cout << v + 1 << ' ';
  cout << endl;

  return 0;
}
