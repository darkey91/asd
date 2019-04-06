#include <iostream>
#include <vector>
#include <algorithm>
class DSU {
public:
    DSU(size_t n) {
        rang.assign(n, 0);
        kings.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            kings[i] = i;
        }
    }

    int get(int v) {
        return (v == kings[v]) ? v : get(kings[v]);
    }

    void unionSets(int u, int v) {
        u = get(u);
        v = get(v);
        if (u != v) {
            if (rang[u] > rang[v]) {
                int t = v;
                v = u;
                u = t;
            }
            kings[u] = v;
            if (rang[u] == rang[v]) ++rang[v];
        }
    }

private:
    size_t n;
    std::vector<int> kings;
    std::vector<int> rang;
};

int main() {
    size_t n, m;
    std::cin >> n >> m;
    DSU dsu(n);
    std::vector<std::pair<std::pair<int, int>, int>> edges;
    for (int i = 0; i < m; ++i) {
        int b, e, w;
        std::cin >> b >> e >> w;
        --b, --e;
        edges.emplace_back(std::make_pair(std::make_pair(b, e), w));
    }

    sort(edges.begin(), edges.end(),
         [](const std::pair<std::pair<int, int>, int> &a, const std::pair<std::pair<int, int>, int> &b) -> bool {
             return a.second < b.second;
         });

    unsigned long long  ans = 0;

    for (int i = 0; i < m; ++i) {
        int v = dsu.get(edges[i].first.first);
        int u = dsu.get(edges[i].first.second);
        if (u != v) {
            ans += edges[i].second;
            dsu.unionSets(edges[i].first.first, edges[i].first.second);
        }
    }
    std::cout << ans;
    return 0;

}
