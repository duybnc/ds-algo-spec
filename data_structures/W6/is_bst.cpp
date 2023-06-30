#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};
vector<Node> tree;
void inOrder(vector<int> &result, int index=0) {
    if (index == -1) return;
    inOrder(result, tree[index].left);
    result.push_back(tree[index].key);
    inOrder(result, tree[index].right);
}
vector <int> in_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    inOrder(result);
    return result;
}


bool IsBinarySearchTree() {
  // Implement correct algorithm here
  if(tree.size() > 1) {
      vector<int> nodes = in_order();
      for (size_t i = 1; i < nodes.size(); i++) {
          if (nodes[i] < nodes[i-1]) return false;
      }
  }
  return true;
}

int main() {
  int nodes;
  cin >> nodes;

  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree()) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
