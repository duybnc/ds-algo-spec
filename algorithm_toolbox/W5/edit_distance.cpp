//
// Created by Duy Bui on 5/11/2023.
//
#include <iostream>
#include <string>

using std::string;

int edit_distance(const string &str1, const string &str2) {
    //check slides for implement
    int D[str1.size()+1][str2.size()+1];
    int index = 0;
    while (index <= str1.size()) {
        D[index][0] = index;
        index++;
    }
    index = 1;
    while (index <= str2.size()) {
        D[0][index] = index;
        index++;
    }
    for (int i=1; i<= str1.size(); i++) {
        for (int j=1; j <= str2.size(); j++) {
            if(str1[i-1] != str2[j-1]) {
                D[i][j] = std::min(1 + D[i-1][j], std::min(1 + D[i-1][j-1], 1+ D[i][j-1]));
            } else {
                D[i][j] = D[i-1][j-1];
            }
        }
    }
    return D[str1.size()][str2.size()];
}

int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    return 0;
}
