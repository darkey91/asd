#include <vector>
#include <iostream>
#include <set>

std::vector<bool> used;
std::vector<int> timeIn, up;
std::set<int> bridges;
int timer = 0;

void dfs(const std::vector<std::vector<std::pair<int, int>>> &g, int v, int p) {
    used[v] = true;
    timeIn[v] = ++timer;
    up[v] = timeIn[v];

    for (auto u: g[v]) {
        if (p == u.first) {
            continue;
        }
        if (!used[u.first]) {
            dfs(g, u.first, v);
            up[v] = std::min(up[v], up[u.first]);
            if (timeIn[v] < up[u.first]) {
                bridges.insert(u.second);
            }
        } else {
            up[v] = std::min(up[v], timeIn[u.first]);
        }
    }

}

int main() {
    int n, m, u, v;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> g(n);
    used.assign(n, false);
    timeIn.assign(n, 0);
    up.assign(n, 0);

    for (int i = 1; i <= m; ++i) {
        std::cin >> u >> v;
        --u, --v;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) dfs(g, i, -1);
    }

    std::cout << bridges.size() << "\n";
    for (auto b: bridges) std::cout << b << " ";

}