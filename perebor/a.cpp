#include <algorithm>
#include <fstream>
#include <vector>
 
 
int main() {
    int k, n;
    std::ifstream in("cobbler.in");
    std::ofstream out("cobbler.out");
    in >> k >> n;
    int ans = 0, time = 0;
    std::vector<int> shoes;
    int q;
    for (int i = 0; i < n; ++i) {
        in >> q;
        shoes.push_back(q);
    }
    sort(shoes.begin(), shoes.end());
 
    for (auto it : shoes) {
        if (time + it <= k) {
            time += it;
            ++ans;
        }
        else break;
    }
 
    out << ans;
    return 0;
}
