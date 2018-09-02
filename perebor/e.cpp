#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    int n, s, a, b;
    ifstream in("apples.in");
    ofstream out("apples.out");

    in >> n >> s;

    vector<pair<pair<int, int>, int>> v, arr, brr;

    for (int i = 0; i < n; ++i) {
        in >> a >> b;
        v.push_back(make_pair(make_pair(a, b), i + 1));
        if (b - a >= 0) {
            arr.push_back(make_pair(make_pair(a, b), i + 1));
        }
        else {
            brr.push_back(make_pair(make_pair(a, b), i + 1));
        }
    }

    vector<int> ind;
    sort(arr.begin(), arr.end(), [](pair<pair<int, int>, int> &l, pair<pair<int, int>, int> &r) {
       return l.first.first < r.first.first;
    });

    sort(brr.begin(), brr.end(), [](pair<pair<int, int>, int> &l, pair<pair<int, int>, int> &r) {
        return l.first.second > r.first.second;
    });


    for (auto it: arr) {
        s = s - it.first.first;
        if (s <= 0) {
            out << "-1";
            return 0;
        }
        s = s + it.first.second;

        ind.push_back(it.second);
    }

    for (auto it: brr) {
        s = s - it.first.first;
        if (s <= 0) {
            out << "-1";
            return 0;
        }
        s = s + it.first.second;
        ind.push_back(it.second);
    }

    if (s > 0)
    for (auto it: ind) {
        out << it << " ";
    }
    else out << "-1";

    return 0;
}