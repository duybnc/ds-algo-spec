#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
using std::numeric_limits;

int distance(vector<vector<int> > &adj, int s, int t) {
  //write your code here
  const int max_int =  numeric_limits<int>::max();
  if (s == t) return 0;
  vector<int> dist (adj.size(), max_int);
  dist[s] = 0;
  queue<int> Q;
  Q.push(s);
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      if (dist[v] == max_int) {
        Q.push(v);
        dist[v] = dist[u] +1;
      }
    }
  }
  if (dist[t] != max_int) return dist[t];
  return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
