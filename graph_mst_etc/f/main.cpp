#include <iostream>
#include <set>
#include <vector>

std::vector<bool> used;
std::vector<int> top, comp;
int comonents = 0;

void dfs(const std::vector<std::set<int>> &g, int v, int p) {
    used[v] = true;
    for (int u: g[v]) {
        if (!used[u]) dfs(g, u, v);
    }
    top.push_back(v);
}

void dfs(const std::vector<std::set<int>> &gT, int v) {
    used[v] = true;
    comp[v] = comonents;
    for (int u: gT[v]) {
        if (!used[u]) dfs(gT, u);
    }
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    std::vector<std::set<int>> g(n, std::set<int>()), gT(n, std::set<int>());
    comp.assign(n, 0);
    used.assign(n, false);
    std::vector<std::pair<int, int>> edges(m);

    for (size_t i = 0; i < m; ++i) {
        int v, u;
        std::cin >> v >> u;
        --u, --v;
        if (v != u) {
            if (g[v].insert(u).second) {
                gT[u].insert(v);
                edges[i] = std::make_pair(v, u);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) dfs(g, i, -1);
    }

    used.assign(n, false);

    for (int i = int(n) - 1; i >= 0; --i) {
        if (!used[top[i]]) {
            dfs(gT, top[i]);
            ++comonents;
        }
    }

    std::set<std::pair<int, int>> compEdges;

    int ans = 0;
    for (int i = 0; i < m; ++i) {
        if (comp[edges[i].second] != comp[edges[i].first])
            if (compEdges.insert(std::make_pair(comp[edges[i].first], comp[edges[i].second])).second) {
                ++ans;
            }
    }

    std::cout << ans;

    return 0;
}