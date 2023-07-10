#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::numeric_limits;

const int max_int =  numeric_limits<int>::max();
struct Vertex {
    int index, distance;
    Vertex(int a = 0, int b = 0): index(a), distance(b) {}
};

struct cmp {
    bool operator() (Vertex a, Vertex b) {
      return a.distance > b.distance;
    }
};

long long distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code her
  vector<int> dist(adj.size(), max_int);
  dist[s] = 0;
  priority_queue<Vertex, vector<Vertex>, cmp> H;
  H.push(Vertex(s, dist[s]));
  while (!H.empty()) {
    Vertex u = H.top();
    H.pop();
    int u_index = u.index;
    for (size_t i =0; i < adj[u_index].size(); i++) {
      int v = adj[u_index][i];
      if (dist[v] > dist[u_index] + cost[u_index][i]) {
        dist[v] = dist[u_index] + cost[u_index][i];
        H.push(Vertex(v, dist[v]));
      }
    }
  }
  if(dist[t] == max_int) return -1;
  return dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
