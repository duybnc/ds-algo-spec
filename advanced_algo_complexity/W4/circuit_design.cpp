#include <iostream>
#include <utility>
#include <vector>
#include <stack>
#include <unordered_map>
#include <limits>
using namespace std;

// Detail:
// - https://en.wikipedia.org/wiki/Tarjan's_strongly_connected_components_algorithm
// - https://en.wikipedia.org/wiki/2-satisfiability
const int  MIN = numeric_limits<int>::min();

struct Clause {
    int index, low, id;
    bool on_stack;
    vector<int> edges;
    Clause(): index(MIN), low(MIN), id(-1), on_stack(false) {}
};

struct TwoSatisfiability {
    int t = 0, id = 0, w = 0, n = 0;
    unordered_map<int, Clause> graph;
    vector<bool> sol;
    stack<int> s;
    bool isSatis = true;

    TwoSatisfiability(unordered_map<int, Clause> adj, int num) :
        n(num), graph(std::move(adj)), sol(vector<bool> (n, false))
    {  }

    void process_vertex(int v) {
      auto &clause = graph[v];

      clause.low = clause.index = t++;
      clause.on_stack = true;
      s.push(v);

      for (auto w : clause.edges) {
        if (graph[w].index == MIN) {
          process_vertex(w);
          clause.low = min(clause.low, graph[w].low);
        } else if (graph[w].on_stack)
          clause.low = min(clause.low, graph[w].index);
      }

      if (clause.low == clause.index) {
        do {
          w = s.top();
          s.pop();

          if (id == graph[-w].id) {
            isSatis = false;
            return;
          }

          auto &w_utl = graph[w];
          w_utl.on_stack = false;
          w_utl.id = id;

          sol[abs(w) - 1] = w < 0 ? true : false;

        } while (w != v);
        id++;
      }
    }
    void print_solution() const noexcept {
      if (!isSatis) {
        cout << "UNSATISFIABLE" << endl;
        return;
      }
      cout << "SATISFIABLE" << endl;
      for (int i = 0, s = sol.size(); i < s; i++) {
        int ans = sol[i] ? i + 1 : -(i + 1);
        cout << ans << " ";
      }
      cout << endl;
    }
    void solve() {
      for (int i = -n; i <= n; ++i) {
        if (graph[i].index == MIN && i != 0)
          process_vertex(i);
      }
      print_solution();
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    unordered_map<int, Clause> adj(n * 2);
    for (int i = 0, x, y; i < m; i++) {
      cin >> x >> y;
      adj[-x].edges.emplace_back(y);
      adj[-y].edges.emplace_back(x);
    }

    TwoSatisfiability ts(adj, n);
    ts.solve();

    return 0;
}
