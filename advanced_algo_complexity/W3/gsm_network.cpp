#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    vector<Edge> edges;
    int color = 3;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula() {
        // This solution prints a simple satisfiable formula
        // and passes about half of the tests.
        // Change this function to solve the problem.
      const int C = color * edges.size() + numVertices;
      const int V = numVertices * color;
      cout << C << " " << V << endl;
      for (size_t i = 0, j = 1; i < numVertices; i++, j += color )
        cout << j << " " << j + 1 << " " << j + 2 << " " << 0 << endl;
      for (Edge &e: edges) {
        cout << -((e.from - 1) * color + 1) << " " << -((e.to - 1) * color + 1) << " " << 0 << endl;
        cout << -((e.from - 1) * color + 2) << " " << -((e.to - 1) * color + 2) << " " << 0 << endl;
        cout << -((e.from - 1) * color + 3) << " " << -((e.to - 1) * color + 3) << " " << 0 << endl;
      }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
