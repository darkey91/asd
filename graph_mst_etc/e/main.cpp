#include <set>
#include <iostream>
#include <vector>
#include <map>

std::map<std::pair<int, int>, int> eComp;
std::vector<int> timeIn, up;
std::vector<bool> used, isPoint;
int timer = 0, colors = 0;

void dfsComp(const std::vector<std::set<int>> &g, int v, int p, int compColor) {
    used[v] = true;

    for (int u: g[v]) {
        if (u == p) continue;
        if (!used[u]) {
            if (up[u] >= timeIn[v]) {
                ++colors;
                eComp.insert(std::make_pair(std::make_pair(u, v), colors));
                eComp.insert(std::make_pair(std::make_pair(v, u), colors));

                dfsComp(g, u, v, colors);
            } else {
                eComp.insert(std::make_pair(std::make_pair(u, v), compColor));
                eComp.insert(std::make_pair(std::make_pair(v, u), compColor));

                dfsComp(g, u, v, compColor);
            }
        } else if (timeIn[u] < timeIn[v]) {

            eComp.insert(std::make_pair(std::make_pair(u, v), compColor));
            eComp.insert(std::make_pair(std::make_pair(v, u), compColor));

        }
    }
}

void dfs(const std::vector<std::set<int>> &g, int v, int p) {
    used[v] = true;
    timeIn[v] = ++timer;
    up[v] = timeIn[v];
    int children = 0;

    for (int u: g[v]) {
        if (p == u) continue;
        if (used[u]) {
            up[v] = std::min(up[v], timeIn[u]);
        } else {
            ++children;
            dfs(g, u, v);
            up[v] = std::min(up[v], up[u]);
            if (up[u] >= timeIn[v] && p != -1) {
                isPoint[v] = true;
            }
        }
    }

    if (p == -1 && children >= 2) {
        isPoint[v] = true;
    }
}

int main() {
    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::set<int>> g(n, std::set<int>());
    std::vector<std::pair<int, int>> edges(m, std::pair<int, int>());
    timeIn.assign(n, 0);
    up.assign(n, 0);
    used.assign(n, false);
    isPoint.assign(n, false);

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> v >> u;
        --u, --v;
        g[v].insert(u);
        g[u].insert(v);
        edges[i] = std::make_pair(v, u);
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) dfs(g, i, -1);
    }

    used.assign(n, false);


    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfsComp(g, i, -1, colors);
        }
    }

    std::cout << colors << std::endl;
    for (int i = 0; i < m; ++i) {
        auto it = eComp.find(std::make_pair(edges[i].first, edges[i].second));
        std::cout << it->second << " ";
    }

    return 0;

}