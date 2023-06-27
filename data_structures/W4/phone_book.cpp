#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::string;
using std::vector;
using std::cin;
using std::map;

struct Query {
    string type, name;
    int number;
};

struct PhoneBook {
    map<int, string> book;
    void Add(string name, int number) {
        book[number] = name;
    }

    void Del(int number) {
        auto position = book.find(number);
        if (position != book.end()) {
            book.erase(position);
        }
    }

    string Find(int number) {
        if (book.find(number) != book.end()) {
            return book[number];
        }
        return "not found";
    }

};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    PhoneBook phoneBook;
    for (size_t i = 0; i < queries.size(); ++i) {
        int number = queries[i].number;
        if (queries[i].type == "add") {
            // if we already have contact with such number,
            // we should rewrite contact's name
            phoneBook.Add(queries[i].name, number);
        } else if (queries[i].type == "del") {
            phoneBook.Del(number);
        } else {
            string response = phoneBook.Find(number);
            result.push_back(response);
        }
    }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
