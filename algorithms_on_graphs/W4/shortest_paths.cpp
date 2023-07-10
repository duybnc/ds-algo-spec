#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::numeric_limits;

const int max_int =  numeric_limits<long>::max();

void bfs(vector<vector<int> > &adj,  vector<int> &shortest, queue<int> &Q) {
  vector<int> visited(adj.size());
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    shortest[u] = 0;
    visited[u] = 1;
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      if (!visited[v]) {
        Q.push(v);
      }
    }
  }
}

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
  //write your code here
  reachable[s] = 1;
  distance[s] = 0;
  queue<int> Q;
  for (int i = 0; i < adj.size(); i++) {
    for (int u = 0; u < adj.size(); u++){
      for (int j = 0; j < adj[u].size(); j++) {
        int v = adj[u][j];
        if (distance[u]!= max_int && distance[v] > distance[u] + cost[u][j]) {
          distance[v] = distance[u] + cost[u][j];
          reachable[v] = 1;
          if (i == adj.size() - 1) {
            Q.push(v);
          }
        }
      }
    }
  }

  bfs(adj, shortest, Q);
  distance[s] = 0;
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
