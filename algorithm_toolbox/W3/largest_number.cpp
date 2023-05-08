#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
bool larger(string a, string b) {
    string c, d;
    c = a.append(b);
    d = b.append(a);
    return c.compare(d) > 0;
}
string largestNumber(vector<string> a)
{
    std::sort(a.begin(), a.end(), larger);
    std::stringstream ret;
    for (size_t i = 0; i < a.size(); i++)
    {
        ret << a[i];
    }
    string result;
    ret >> result;
    return result;
}

int main()
{
    int n;
    std::cin >> n;
    vector<string> a(n);
    for (auto & i : a)
    {
        std::cin >> i;
    }
    std::cout << largestNumber(a);
}
