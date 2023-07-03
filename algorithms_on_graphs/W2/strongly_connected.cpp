#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::pair;
using std::stack;

vector<vector<int>> reverseGraph(vector<vector<int>> &adj) {
    vector<vector<int>> rAdj (adj.size(), vector<int>());
    for (int i= 0; i < adj.size(); i++) {
        for (int j=0; j <adj[i].size(); j++) {
            rAdj[adj[i][j]].push_back(i);
        }
    }
    return rAdj;
}

void dfs(vector<vector<int>> &adj, int x, vector<int> &visited, stack<int> &nodes) {
    visited[x] =1;
    for(int i =0; i < adj[x].size(); i++) {
        if(!visited[adj[x][i]]) {
            visited[adj[x][i]] = 1;
            dfs(adj, adj[x][i], visited, nodes);
        }
    }
    nodes.push(x);
}

int number_of_strongly_connected_components(vector<vector<int> > adj) {
  int result = 0;
  stack<int> nodes;
  vector<int> visited(adj.size(), 0);
  for (int i=0; i < adj.size(); i++) {
      if (!visited[i]) dfs(adj, i, visited, nodes);
  }
  vector<vector<int> > rAdj = reverseGraph(adj);

  vector<int> rVisited(adj.size(), 0);
  while (!nodes.empty()) {
      int x = nodes.top();
      nodes.pop();
      if (!rVisited[x]) {
          stack<int> componentNodes;
          dfs(rAdj, x, rVisited, componentNodes);
          result++;
      }
  }
  return result;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << number_of_strongly_connected_components(adj);
}
