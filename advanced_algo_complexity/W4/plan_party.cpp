#include <iostream>
#include <vector>

struct Vertex {
    int weight;
    std::vector <int> children;
};
typedef std::vector<Vertex> Graph;
typedef std::vector<int> Sum;

Graph ReadTree() {
    int vertices_count;
    std::cin >> vertices_count;

    Graph tree(vertices_count);

    for (int i = 0; i < vertices_count; ++i)
        std::cin >> tree[i].weight;

    for (int i = 1; i < vertices_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to;
        tree[from - 1].children.push_back(to - 1);
        tree[to - 1].children.push_back(from - 1);
    }

    return tree;
}

void dfs(const Graph &tree, int vertex, int parent) {
    for (int child : tree[vertex].children)
        if (child != parent)
            dfs(tree, child, vertex);

    // This is a template function for processing a tree using depth-first search.
    // Write your code here.
    // You may need to add more parameters to this function for child processing.
}

int compute_recursively(const Graph &tree, const int vertex, Sum &s, const int parent) {
  if (s[vertex] == -1) {
    if (tree[vertex].children.empty())
      s[vertex] = tree[vertex].weight;
    else {
      int m1 = tree[vertex].weight;
      for (int u : tree[vertex].children) {
        if (u == parent)
          continue;
        for (int w : tree[u].children) {
          if (w != vertex)
            m1 += compute_recursively(tree, w, s, u);
        }
      }
      auto m0 = 0;
      for (int u : tree[vertex].children) {
        if (u != parent)
          m0 += compute_recursively(tree, u, s, vertex);
      }
      s[vertex] = std::max(m1, m0);
    }
  }

  return s[vertex];
}

int MaxWeightIndependentTreeSubset(const Graph &tree) {
    size_t size = tree.size();
    if (size == 0)
        return 0;
    auto s = Sum (size, -1);
    // You must decide what to return.
    return compute_recursively(tree, 0, s, -1);
}

int main() {
    // This code is here to increase the stack size to avoid stack overflow
    // in depth-first search.
//    const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
//    struct rlimit rl;
//    int result;
//    result = getrlimit(RLIMIT_STACK, &rl);
//    if (result == 0)
//    {
//        if (rl.rlim_cur < kStackSize)
//        {
//            rl.rlim_cur = kStackSize;
//            result = setrlimit(RLIMIT_STACK, &rl);
//            if (result != 0)
//            {
//                fprintf(stderr, "setrlimit returned result = %d\n", result);
//            }
//        }
//    }

    // Here begins the solution
    Graph tree = ReadTree();
    int weight = MaxWeightIndependentTreeSubset(tree);
    std::cout << weight << std::endl;
    return 0;
}
