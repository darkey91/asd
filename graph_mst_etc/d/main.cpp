    #include <iostream>
    #include <vector>
    #include <set>
    #include <map>

    std::map<std::pair<int, int>, int> amountEdges;
    std::vector<int> timeIn, comp, up;
    std::vector<bool> used;
    int timer = 0, cnt = 0;

    void dfs(const std::vector<std::vector<int>> &g, int v, int p) {
        used[v] = true;
        timeIn[v] = ++timer;
        up[v] = timeIn[v];

        for (int u: g[v]) {
            if (p == u ) continue;
            if (used[u]) {
                up[v] = std::min(up[v], timeIn[u]);
            } else {
                dfs(g, u, v);
                up[v] = std::min(up[v], up[u]);
            }
        }
    }

    void dfsBridge(const std::vector<std::vector<int>> &g, int v, int compCnt) {
        comp[v] = compCnt;

        for (int u: g[v]) {
            if (comp[u] == 0) {
                if (up[u] > timeIn[v] && amountEdges.find(std::make_pair(v, u))->second == 1) {
                    ++cnt;
                    dfsBridge(g, u, cnt);
                } else {
                    dfsBridge(g, u, compCnt);
                }
            }
        }
    }

    int main() {
        int n, m, u, v;
        std::cin >> n >> m;

        std::vector<std::vector<int>> g(n, std::vector<int>());;

        used.assign(n, false);
        timeIn.assign(n, 0);
        up.assign(n, 0);
        comp.assign(n, 0);

        for (int i = 0; i < m; ++i) {
            std::cin >> u >> v;
            if (u != v) {
                --u, --v;
                g[u].push_back(v);
                g[v].push_back(u);
                if (amountEdges.count(std::make_pair(u, v)) > 0) {
                    amountEdges.find(std::make_pair(u, v))->second += 1;
                    amountEdges.find(std::make_pair(v, u))->second += 1;
                } else {
                    amountEdges.insert(std::make_pair(std::make_pair(u,v),1));
                    amountEdges.insert(std::make_pair(std::make_pair(v,u),1));

                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                dfs(g, i, -1);
            }
        }

        for (int i = 0; i < n; ++i) {
            if (comp[i] == 0) {
                ++cnt;
                dfsBridge(g, i, cnt);
            }
        }
        std::cout << cnt << "\n";
        for (int i = 0; i < n; ++i) {
            std::cout << comp[i] << " ";
        }

        return 0;
    }