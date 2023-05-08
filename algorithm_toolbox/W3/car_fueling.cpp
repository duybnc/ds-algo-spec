#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::max;
using std::vector;

int compute_min_refills(int dist, int tank, vector<int> &stops)
{
    int ans = 0;
    if (dist <= tank)
        return ans;
    int remain = tank;
    int start = 0;
    for (int i = 0; i < stops.size(); i++)
    {
        int nextStop = 0;
        if ((i + 1) == stops.size()) {
            nextStop = dist;
        } else {
            nextStop = stops[i + 1];
        }

        if ((nextStop - stops[i]) > tank)
            return -1;
        remain -= (stops[i] - start);
        if ((nextStop - stops[i]) > remain)
        {
            ans += 1;
            remain = tank;
        }
        start = stops[i];
    }
    return ans;
}

int main()
{
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
