//
// Created by Duy Bui on 5/23/2023.
//
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
        this->parent = NULL;
    }

    void setParent(Node *theParent) {
        parent = theParent;
        parent->children.push_back(this);
    }
};


int main_with_large_stack_space() {
    std::ios_base::sync_with_stdio(0);
    int n;
    std::cin >> n;

    std::vector<Node> nodes (n);
    int root = 0;
    for (int child_index = 0; child_index < n; child_index++) {
        int parent_index;
        std::cin >> parent_index;
        if (parent_index >= 0)
            nodes[child_index].setParent(&nodes[parent_index]);
        nodes[child_index].key = child_index;
        if (parent_index == -1) root = child_index;
    }
    int height = 0;
    std::queue<Node> q;
    q.push(nodes[root]);
    while (!q.empty()) {
        // breadth-first search
        size_t s = q.size();
        for (int i = 0; i < s; i++) {
            Node temp = q.front();
            q.pop();
            if (!temp.children.empty()) {
                for (size_t i= 0; i < temp.children.size(); i++) {
                    q.push(*temp.children[i]);
                }
            }
        }
        height++;
    }

    std::cout << height << std::endl;
    return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
    return main_with_large_stack_space();
}
//Failed case #3/24: (Wrong answer)
//
//Input:
//10
//9 7 5 5 2 9 9 9 2 -1
//
//Your output:
//2
//
//Your stderr:
//setrlimit returned result = -1
//
//Correct output:
//4