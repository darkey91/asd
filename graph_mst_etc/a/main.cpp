#include <set>
#include <vector>
#include <iostream>

using std::vector;
using std::set;

vector<int> s;
vector<int> used;
bool hasCycle = false;

void dfs(const vector<vector<int> > &g, int v) {
    used[v] = 1;

    for (int u: g[v]) {
        if (used[u] == 0) {
            dfs(g, u);
        } else if (used[u] == 1) {
            hasCycle = true;
        }
    }
    used[v] = 2;
    s.push_back(v + 1);
}

int main() {
    int n, m, u, v;

    std::cin >> n >> m;

    vector<vector<int> > graph(n);
    used.assign(n, 0);

    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        --u, --v;
        graph[u].push_back(v);

    }

    for (int v = 0; v < n; ++v) {
        if (used[v] == 0)
            dfs(graph, v);
    }
    if (hasCycle) {
        std::cout << -1;
    } else {
        for (int i = (int) s.size() - 1; i >= 0; --i) {
            std::cout << s[i] << " ";
        }
    }
    return 0;
}
