#include <vector>
#include <set>
#include <iostream>

std::vector<bool> used;
std::vector<int> timeIn, up;
std::set<int> points;
int timer = 0;

void dfs(const std::vector<std::vector<int>> &g, int v, int p) {
    used[v] = true;
    timeIn[v] = ++timer;
    up[v] = timeIn[v];

    int cnt = 0;

    for (int u: g[v]) {
        if (p == u) continue;

        if (used[u]) {
            up[v] = std::min(up[v], timeIn[u]);
        } else {
            ++cnt;
            dfs(g, u, v);
            up[v] = std::min(up[v], up[u]);
            if (up[u] >= timeIn[v] && p != -1)
                points.insert(v + 1);
        }
    }
    if (cnt >= 2 && p == -1)
        points.insert(v + 1);

}

int main() {
    int n, m, u, v;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n);
    used.assign(n, false);
    timeIn.assign(n, 0);
    up.assign(n, 0);

    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        --u, --v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    for (int v = 0; v < n; ++v) {
        if (!used[v]) dfs(g, v, -1);
    }

    std::cout << points.size() << "\n";
    for (int p: points) std::cout << p << " ";
    return 0;
}