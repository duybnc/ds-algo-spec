#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>

using std::vector;
using std::pair;

struct Node {
    int x, y, parent, rank;
    Node(int x, int y, int parent = -1, int rank =0): x(x), y(y), parent(parent), rank(rank) {}
};

struct Edge {
    int u, v;
    double weight;
    Edge(int u, int v, double weight): u(u), v(v), weight(weight) {}
};

bool cmp(Edge a, Edge b) { return a.weight < b.weight; }

void make_set(int i, vector<Node> &nodes, vector<int> &x, vector<int> &y) {
  nodes.push_back(Node(x[i], y[i], i));
}

double weight(int x1, int y1, int x2, int y2) {
  return (double) sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int Find(int i, vector<Node> &nodes) {
  if (i != nodes[i].parent) {
    nodes[i].parent = Find(nodes[i].parent, nodes);
  }
  return nodes[i].parent;
}

void Union(int u, int v, vector<Node> &nodes) {
  int r1 = Find(u, nodes);
  int r2 = Find(v, nodes);
  if (r1 != r2) {
    if (nodes[r1].rank > nodes[r2].rank) {
      nodes[r2].parent = r1;
    } else {
      nodes[r1].parent = r2;
      if (nodes[r1].rank == nodes[r2].rank) {
        nodes[r2].rank++;
      }
    }
  }
}


double clustering(vector<int> x, vector<int> y, int k) {
  //write your code here
  int n = x.size();
  vector<Node> nodes;
  for (int i = 0; i < n; i++) {
    make_set(i, nodes, x, y);
  }
  vector<Edge> edges;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      edges.push_back(Edge(i, j, weight(x[i], y[i], x[j], y[j])));
    }
  }
  std::sort(edges.begin(), edges.end(), cmp);
  int union_num = 0;
  for (int i = 0; i < edges.size(); i++) {
    Edge current_edge = edges[i];
    int u = current_edge.u;
    int v = current_edge.v;
    if (Find(u, nodes) != Find(v, nodes)) {
      union_num++;
      Union(u, v, nodes);
    }
    if(union_num > n - k) return current_edge.weight;
  }
  return -1.;
} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
