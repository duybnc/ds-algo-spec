#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
const int non_color =  -1;
int bfs(vector<vector<int> > &adj, vector<int> &dist, int s) {
  dist[s] = 1;
  queue<int> Q;
  Q.push(s);
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      // two vertices have same color but have an edge => not bipartite
      if (dist[v] == dist[u]) return 0;
      if (dist[v] == non_color) {
        // opposite color
        dist[v] = 1 - dist[u];
        Q.push(v);
      }
    }
  }
  return 1;
}

int bipartite(vector<vector<int> > &adj) {
  //write your code here
  vector<int> dist (adj.size(), non_color);
  int result = 1;
  // BFS each connected components
  for (int i = 0; i <dist.size(); i++) {
    if (dist[i] == non_color) result = bfs(adj, dist, i);
    if (!result) return  result;
  }
  return result;
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
  std::cout << bipartite(adj);
}
