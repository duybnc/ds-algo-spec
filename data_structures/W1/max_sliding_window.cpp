//
// Created by Duy Bui on 5/23/2023.
//
#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

using std::cin;
using std::cout;
using std::vector;
using std::max;

void max_sliding_window_naive(vector<int> const & A, int w) {
    for (size_t i = 0; i < A.size() - w + 1; ++i) {
        int window_max = A.at(i);
        for (size_t j = i + 1; j < i + w; ++j)
            window_max = max(window_max, A.at(j));

        cout << window_max << " ";
    }

    return;
}

class StackWithMax {
    std::stack<int> stack;
    std::stack<int> trackMax;
public:

    void Push(int value) {
        stack.push(value);
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
        if (!stack.empty()) {
            stack.pop();
            trackMax.pop();
        }

    }

    int Max()  {
        return trackMax.top();
    }

    bool Empty() {
        return stack.empty();
    }

    int Top() {
        return stack.top();
    }
};

struct Queue {
    StackWithMax s1;
    StackWithMax s2;
    void enQueue(int x) {
        s1.Push(x);
    }
    void deQueue() {
        if (s2.Empty()) {
            while (!s1.Empty()) {
                s2.Push(s1.Top());
                s1.Pop();
            }
        }
        s2.Pop();
    }

    int Max() {
        int s1_max = 0;
        if (!s1.Empty()) {
            s1_max = s1.Max();
        }
        int s2_max = 0;
        if (!s2.Empty()) {
            s2_max = s2.Max();
        }
        return max(s1_max, s2_max);
    }
};
void max_sliding_window(vector<int> const & A, int w) {
    Queue q;
    for (size_t i =0; i< w; i++) {
        q.enQueue(A[i]);
    }
    for (size_t i = w; i <= A.size(); i++) {
        cout << q.Max() << " ";
        q.deQueue();
        q.enQueue(A[i]);
    }
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

//    max_sliding_window_naive(A, w);
    max_sliding_window(A, w);

    return 0;
}
