#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;
int main() {
    ifstream in("request.in");
    ofstream out("request.out");
 
    int n;
    vector<pair<int, int>> lessons;
    in >> n;
    vector<bool> isOk(n, true);
    for (int i = 0; i < n; ++i) {
        int q, w;
        in >> q >> w;
        lessons.push_back(make_pair(q, w));
    }
    sort(lessons.begin(), lessons.end(), [](auto &l, auto &r) {
        return l.second < r.second;
    });
 
    int ans = 0, last = 0;
 
    for (int i = 0; i < lessons.size(); ++i) {
        if (lessons[i].first < last)
            isOk[i] = false;
        if (isOk[i]) {
            ++ans;
            last = lessons[i].second;
        }
    }
 
    out << ans;
 
    return 0;
}
