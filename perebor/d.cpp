#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int n;

vector<pair<int, int>> p;

int bin_search(int left, int right, int val) {
    int l = left;
    int r = right;
    while (l < r - 1) {
        int m = (l + r) >> 1;
        if (p[m].first <= val) l = m;
        else r = m;
    }

    return l;
};

int main() {
    ifstream in("sequence.in");
    ofstream out("sequence.out");
    int tmp, sum = 0;
    in >> n;
    for (int i = 0; i < n; ++i) {
        in >> tmp;

        p.push_back(make_pair(tmp, i + 1));
        sum += tmp;
    }

    if (sum % 2 != 0) {
        out << "-1" << "\n";
        return 0;
    }

    sum /= 2;

    sort(p.begin(), p.end(), [](auto &l, auto &r) {
        return l.first < r.first;
    });

    set<int> ind;
    tmp = p[0].first;
    ind.insert(p[0].second);

    int l = 1, r = p.size();
    while (tmp < sum) {
        int i = bin_search(l, r, sum - tmp);
        tmp += p[i].first;
        ind.insert(p[i].second);
        r = i;
    }
    if (tmp == sum) {
        out << ind.size() << "\n";
        for (auto it: ind) {
            out << it << " ";
        }
    } else {
        out << "-1";
    }

    return 0;
}
