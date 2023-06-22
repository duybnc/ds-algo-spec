//
// Created by Duy Bui on 5/23/2023.
//
#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
            type(type),
            position(position)
    {}

    bool Match(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(Bracket(next, position + 1));
        }

        if (next == ')' || next == ']' || next == '}') {
            if (opening_brackets_stack.empty()) {
                std::cout << position + 1;
                return 0;
            }
            Bracket top = opening_brackets_stack.top();
            opening_brackets_stack.pop();
            if (!top.Match(next)) {
                std::cout << position +1;
                return 0;
            }
        }
    }
    if (!opening_brackets_stack.empty()) {
        Bracket top = opening_brackets_stack.top();
        std::cout << top.position;
        return 0;
    }
    std::cout << "Success";

    return 0;
}
