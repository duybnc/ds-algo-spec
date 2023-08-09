#include <ios>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>

using namespace std;

struct ConvertILPToSat {
    vector< vector<int> > A;
    vector<int> b;
    bitset<3> combinations;
    string stream;

    ConvertILPToSat(int n, int m) : A(n, vector<int>(m)), b(n)
    {}

    void printEquisatisfiableSatFormula() {
        // This solution prints a simple satisfiable formula
        // and passes about half of the tests.
        // Change this function to solve the problem.
      int cnt = 0;
      for (size_t i = 0; i < A.size(); i++) {
        const auto &row = A[i];

        int n = count_if(row.begin(), row.cend(), [](const auto a) { return a != 0; });

        for (int j = 0, s = pow(2, n); j < s; ++j) {
          combinations = j;
          int sum = 0, c = 0;
          for (const auto x : row) {
            if (x != 0 && combinations[c++])
              sum += x;
          }

          if (sum > b[i]) {
            bool is_clause = false;
            for (int k = 0, comb = 0; k < row.size(); ++k) {
              if (row[k] != 0) {
                stream += combinations[comb] ? (std::to_string(-(k + 1)) + ' ') : (std::to_string(k + 1) + ' ');
                ++comb;
                is_clause = true;
              }
            }
            if (is_clause) {
              stream += "0 \n";
              ++cnt;
            }
          }
        }
      }

      if (cnt == 0) {
        cnt++;
        stream += "1 -1 0\n";
      }
      cout << cnt << " " << (A[0].size()) << endl;
      cout << stream.c_str();
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertILPToSat converter(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> converter.A[i][j];
      }
    }
    for (int i = 0; i < n; i++) {
      cin >> converter.b[i];
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
