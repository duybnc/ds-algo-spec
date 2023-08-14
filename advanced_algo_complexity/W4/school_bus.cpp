#include <iostream>
#include <vector>
#include <bitset>

// - https://en.wikipedia.org/wiki/Held%E2%80%93Karp_algorithm
// - https://www.geeksforgeeks.org/traveling-salesman-problem-tsp-implementation/
// - https://en.wikipedia.org/wiki/Travelling_salesman_problem

const int INF = 1e9;
struct Node {
    int dist = INF;
    int parent = 0;
};

using namespace std;
typedef vector<vector<int> > Matrix;
typedef vector<int> subset;
typedef vector<vector<Node>> cost;
typedef pair<int, vector<int>> tour;


Matrix read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    Matrix graph(vertex_count, vector<int>(vertex_count, INF));
    for (int i = 0; i < edge_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        --from, --to;
        graph[from][to] = graph[to][from] = weight;
    }
    return graph;
}

struct TSP {
    const int N;
    cost C;
    Matrix dist;

    TSP(Matrix complete_graph)
    : N{(int)complete_graph.size()}, C{cost(1 << (N), std::vector<Node>(N))}, dist{std::move(complete_graph)}{
      for (int k = 1; k < N; ++k)
        C[1 << k][k] = Node{dist[0][k], 0};
    }

    tour optimal_tour() {
      for (int s = 2; s < 1 << (N - 1); s++) {
        if (s & (s - 1)) {
          subset S = combinations(s);
          int bits = s * 2;

          for (auto k : S) {
            int prev = bits ^ (1 << k);
            Node min_node;

            for (auto m : S)
              if (C[prev][m].dist + dist[m][k] < min_node.dist && k != m)
                min_node = Node{C[prev][m].dist + dist[m][k], m};
            C[bits][k] = min_node;
          }
        }
      }

      return backtrack_optimal();
    }

    subset combinations(const int n) {
      subset combs;
      std::bitset<16> bset = n;

      for (auto k = 0u; k < bset.size(); ++k)
        if (bset[k])
          combs.emplace_back(k + 1);
      return combs;
    }

    tour backtrack_optimal() {
      Node min_node;
      int bits = (1 << N) - 2;

      for (int k = 1; k < N; ++k)
        if (min_node.dist > C[bits][k].dist + dist[k][0])
          min_node = Node{C[bits][k].dist + dist[k][0], k};
      if (min_node.dist == INF)
        return {-1, {}};

      tour optimal_tour;

      optimal_tour.second.reserve(N);
      optimal_tour.first = min_node.dist;
      optimal_tour.second.emplace_back(1);

      for (int i = 0; i < N - 1; ++i) {
        optimal_tour.second.emplace_back(min_node.parent + 1);
        min_node.parent = C[bits][min_node.parent].parent;
        bits = bits ^ (1 << (optimal_tour.second.back() - 1));
      }

      return optimal_tour;
    }
};

void print_answer(const std::pair<int, vector<int> >& answer) {
    std::cout << answer.first << "\n";
    if (answer.first == -1)
        return;
    const vector<int>& path = answer.second;
    for (size_t i = 0; i < path.size(); ++i)
        std::cout << path[i] << " ";
    std::cout << "\n";
}

int main() {
    TSP tsp(read_data());
    print_answer(tsp.optimal_tour());
    return 0;
}
