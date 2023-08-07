#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <bitset>
#include <numeric>
using namespace std;

const long double EPS = 1e-3;
const long double INFINITY_NUM = 1.0e+9;
const int PRECISION = 20;

typedef std::vector<long double> Column;
typedef std::vector<long double> Row;
typedef std::vector<Row> Matrix;

struct Equation {
    Equation(const Matrix &a, const Column &b):
            a(a),
            b(b)
    {}

    Matrix a;
    Column b;
};

struct Position {
    Position(int column, int row):
            column(column),
            row(row)
    {}

    int column;
    int row;
};

Position SelectPivotElement(
        const Matrix &a,
        std::vector <bool> &used_rows,
        std::vector <bool> &used_columns) {
  // This algorithm selects the first free element.
  // You'll need to improve it to pass the problem.
  Position pivot_element(0, 0);
  while (used_rows[pivot_element.row])
    ++pivot_element.row;
  while (used_columns[pivot_element.column])
    ++pivot_element.column;
  // Select a pivot with the largest value
  long double max = 0.0;
  for (int i = pivot_element.row; i < a.size(); i++) {
    if (std::fabs(a[i][pivot_element.column]) > std::fabs(max)) {
      max = a[i][pivot_element.column];
      pivot_element.row = i;
    }
  }
  return pivot_element;
}

void SwapLines(Matrix &a, Column &b, std::vector <bool> &used_rows, Position &pivot_element) {
  std::swap(a[pivot_element.column], a[pivot_element.row]);
  std::swap(b[pivot_element.column], b[pivot_element.row]);
  std::swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
  pivot_element.row = pivot_element.column;
}

void ScalePivot(Matrix &a, Column &b, const Position &pivot_element) {
  const long double divisor = a[pivot_element.row][pivot_element.column];
  const int size = a.size();
  for (int i = pivot_element.column; i < size; i++)
    a[pivot_element.row][i] /= divisor;
  b[pivot_element.row] /= divisor;
}

void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element) {
  // Write your code here
  const int s = a.size();
  long double multiple;
  ScalePivot(a, b, pivot_element);
  for (int i = pivot_element.row +1; i < s; i++) {
    multiple = a[i][pivot_element.column];
    for (int j = pivot_element.column; j < s; j++)
      a[i][j] -= (long double) (a[pivot_element.row][j] * multiple);
    b[i] -= (long double) (b[pivot_element.row] * multiple);
  }
}

void MarkPivotElementUsed(const Position &pivot_element, std::vector <bool> &used_rows, std::vector <bool> &used_columns) {
  used_rows[pivot_element.row] = true;
  used_columns[pivot_element.column] = true;
}

void Back(Matrix &a, Column &b) {
  for (int i = a.size() - 1; i; i--) {
    long double v = b[i];
    for (int j = 0; j != i; j++) {
      b[j] -= a[j][i] * v;
    }
  }
}

Column SolveEquation(Equation equation) {
  Matrix &a = equation.a;
  Column &b = equation.b;
  if (a.empty())
    return {};

  int size = a.size();

  std::vector <bool> used_columns(size, false);
  std::vector <bool> used_rows(size, false);
  for (int step = size; step; step--) {
    Position pivot_element = SelectPivotElement(a, used_rows, used_columns);
    if (a[pivot_element.row][pivot_element.column] == 0)
      break;
    SwapLines(a, b, used_rows, pivot_element);
    ProcessPivotElement(a, b, pivot_element);
    MarkPivotElementUsed(pivot_element, used_rows, used_columns);
  }
  Back(a ,b);
  return b;
}

vector<vector<int>> GetSubsets(const vector<int> &set, int m)
{
  const int n = pow(2, set.size());
  vector<vector<int>> subsets;
  std::bitset<32> bset;

  for (int i = 0; i < n; i++) {
    bset = bset.to_ulong() + 1l;
    vector<int> subset;
    int s = 0;
    for (int j = 0; j < set.size(); j++) {
      if (bset[set.size() - 1 - j]) {
        subset.push_back(set[j]);
        if (s++ > m)
          break;
      }
    }

    if (s == m)
      subsets.push_back(std::move(subset));
  }
  return subsets;
}

vector<Column> AllEquations(int m, const Matrix &A, const vector<long double> &b)
{
  vector<Column> solutions;
  vector<int> nums(A.size());

  int s = 0;
  generate(nums.begin(), nums.end(), [&s] { return s++; });
  auto subsets = GetSubsets(nums, m);

  if (A.size() == 1)
    subsets.emplace_back(0);
  for (const auto &sub : subsets) {
    Matrix mat;
    Column col;

    for (auto j : sub) {
      mat.push_back(A[j]);
      col.push_back(b[j]);
    }
    Equation eq{std::move(mat), std::move(col)};
    auto solution = SolveEquation(eq);
    if (!solution.empty())
      solutions.emplace_back(std::move(solution));
  }

  return solutions;
}

void Prepare(int &n, const int m, Matrix &A, vector<long double> &b) {
  // make sure matrix is MxM
  while (n < m) {
    A.emplace_back(m, 0);
    b.emplace_back(0);
    n++;
  }

  // add equation to check for infinity
  A.emplace_back(vector<long double>(m, 1));
  b.emplace_back(INFINITY_NUM);
  n++;

  // add equations to check that amount are positive
  for (int k = 0; k < m; k++) {
    vector<long double> vec(m, 0.0);
    vec[k] = -1;
    A.emplace_back(std::move(vec));
    b.emplace_back(-0.0);
    n++;
  }
}

pair<int, vector<long double>> solve_diet_problem(
    int n, 
    int m,
    Matrix A,
    vector<long double> b, 
    vector<long double> c) {

  Prepare(n, m, A, b);
  vector<Column> solutions = AllEquations(m, A, b);

  if (solutions.size() == 0)
  {
    return {-1, {}}; // no solution
  }

  int sol_index = -1;
  long double largest_pleasure = -(std::numeric_limits<long double>::max() / 2);

  // check solutions
  for (int i = 0; i < solutions.size(); i++) {

    auto &sol = solutions[i];
    bool satisfied{true};

    for (int j = 0; j < n; j++) {

      long double constraint = b[j];
      long double sum =0.0;

      for (int k = 0; k < m; k++)
        sum += A[j][k] * sol[k];

      if (sum - constraint > EPS) {
        satisfied = false;
        break;
      }
    }

    long double pleasure = 0.0;
    for (int k = 0; k < m; k++)
      pleasure += sol[k] * c[k];
    if (satisfied && pleasure > largest_pleasure) {
      largest_pleasure = pleasure;
      sol_index = i;
    }
  }

  if (sol_index == -1)
    return {-1, {}}; // no solution

  auto &sol = solutions[sol_index];
  if (std::accumulate(sol.begin(), sol.end(), (long double)0.0) + EPS >= INFINITY_NUM)
    return {1, {}}; // infinity

  return {0, std::move(sol)};
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  Matrix A(n, vector<long double>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
  }
  vector<long double> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<long double> c(m);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }

  pair<int, vector<long double>> ans = solve_diet_problem(n, m, A, b, c);

  switch (ans.first) {
    case -1: 
      printf("No solution\n");
      break;
    case 0: 
      printf("Bounded solution\n");
      for (int i = 0; i < m; i++) {
        printf("%.18Lf%c", ans.second[i], " \n"[i + 1 == m]);
      }
      break;
    case 1:
      printf("Infinity\n");
      break;      
  }
  return 0;
}
