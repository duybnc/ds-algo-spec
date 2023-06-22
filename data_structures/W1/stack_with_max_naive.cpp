//
// Created by Duy Bui on 5/23/2023.
//
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <stack>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;

class StackWithMax {
    vector<int> stack;
    std::stack<int> trackMax;
public:

    void Push(int value) {
        stack.push_back(value);
        if (stack.size() ==1) {
            trackMax.push(value);
            return;
        }
        if (value >=trackMax.top()) {
            trackMax.push(value);
        } else {
            trackMax.push(trackMax.top());
        }

    }

    void Pop() {
        assert(stack.size());
        stack.pop_back();
        trackMax.pop();
    }

    int Max() const {
        return trackMax.top();
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}