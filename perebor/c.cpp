#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    ifstream in("printing.in");
    ofstream out("printing.out");
    int n, t;
    vector<pair<pair<int, double>, double>> tariff;
    in >> n;

    for (int i = 0; i < 7; ++i) {
        in >> t;
        tariff.push_back(make_pair(make_pair(t, pow(10, t)), t / pow(10, i)));
    }

    sort(tariff.begin(), tariff.end(), [](pair<pair<int, double>, double> &l, pair<pair<int, double>, double> &r) {
        if (l.second == r.second) {
            return l.first.second > r.first.second;
        }
        return l.second < r.second;
    });

    return 0;
}