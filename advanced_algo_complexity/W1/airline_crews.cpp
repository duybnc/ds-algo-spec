#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::numeric_limits;
using std::queue;
using std::size_t;

class FlowGraph {
public:
    struct Edge {
        int from, to, capacity, flow;
    };

private:
    vector<Edge> edges;
    vector<vector<size_t> > graph;
    const size_t flights;

public:
    explicit FlowGraph(size_t n, size_t m, size_t f): graph(n), flights(f) {
      edges.reserve(m * 2);
    }

    void add_edge(int from, int to, int capacity) {
      Edge forward_edge = {from, to, capacity, 0};
      Edge backward_edge = {to, from, 0, 0};
      graph[from].push_back(edges.size());
      edges.push_back(forward_edge);
      graph[to].push_back(edges.size());
      edges.push_back(backward_edge);
    }

    size_t size() const {
      return graph.size();
    }

    size_t get_flights() const {
      return flights;
    }

    const vector<size_t>& get_ids(int from) const {
      return graph[from];
    }

    const Edge& get_edge(size_t id) const {
      return edges[id];
    }

    void add_flow(size_t id, int flow) {
      edges[id].flow += flow;
      edges[id ^ 1].flow -= flow;
    }
};

class MaxMatching {
 public:
  void Solve() {
    FlowGraph graph = ReadData();
    FindMatching(graph, 0, graph.size() - 1);
    WriteResponse(graph);
  }

 private:
    FlowGraph ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    FlowGraph graph(num_left + num_right + 2, num_right + num_left + 2, num_left);
    /* Construct FlowGraph from data given for bipartite graph by adding source and sink. */
    /* Edges from vertices on the left of bipartite graph to the source */
    for (int i = 0; i < num_left; ++i) graph.add_edge(0, i + 1, 1);

    /* Edges of vertices from left to right of bipartite graph */
    for (int i = 1; i <= num_left; ++i) {
      for (int j = 0; j < num_right; ++j) {
        int bit;
        std::cin >> bit;
        if (bit == 1) graph.add_edge(i, num_left + j + 1, 1);
      }
    }

    /* Edges from vertices on the right of bipartite graph to the sink */
    for (int i = num_left + 1; i <= num_right + num_left; ++i)
      graph.add_edge(i, num_left + num_right + 1, 1);

    return graph;
  }

  void bfs(const FlowGraph &graph, int from, vector<int> &path) {
      queue<int> Q;
      Q.push(from);
      std::fill(path.begin(), path.end(), -1);
      while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto id : graph.get_ids(u)) {
          const FlowGraph::Edge &edge = graph.get_edge(id);
          if (path[edge.to] == -1 && edge.capacity > edge.flow && edge.to != from) {
            Q.push(edge.to);
            path[edge.to] = id;
          }
        }
      }
    }

  void WriteResponse(FlowGraph& graph) {
    size_t flights = graph.get_flights();
    for (int i = 0; i < flights; ++i) {
      int job = -1;
      for (auto id: graph.get_ids(i + 1)) {
        const FlowGraph::Edge &edge = graph.get_edge(id);
        if (edge.flow == 1) {
          job = edge.to - flights;
          break;
        }
      }
      cout << job << " ";
    }
    cout << "\n";
  }

  void FindMatching(FlowGraph& graph, int from, int to) {
    // Replace this code with an algorithm that finds the maximum
    // matching correctly in all cases.
    vector<int> path(graph.size(), -1);
    do {
      bfs(graph, from, path);
      if (path[to] != -1) {
        int min_flow = numeric_limits<int>::max();
        for (int i = path[to]; i != -1; i = path[graph.get_edge(i).from]) {
          min_flow = std::min(min_flow, graph.get_edge(i).capacity - graph.get_edge(i).flow);
        }
        for (int i = path[to]; i != -1; i = path[graph.get_edge(i).from]) {
          graph.add_flow(i, min_flow);
        }
      }
    } while (path[to] != -1);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.Solve();
  return 0;
}
