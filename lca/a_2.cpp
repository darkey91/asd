#include <stdio.h>
#include <vector>
 
const int N = 2 * 1e5 + 19, K = 19;
int log = 1;
int d[200009], dp[N][K], logs[N];
 
std::vector<std::vector<int>> tree;
 
void dfs(int v, int parent, int dep) {
    dp[v][0] = parent;
    d[v] = dep;
    for (int i = 1; i <= log; ++i) {
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
    }
    for (int i = 0; i < tree[v].size(); ++i) {
        int c = tree[v][i];
        if (c != parent) {
            dfs(c, v, dep + 1);
        }
    }
}
 
int lca(int u, int v) {
    if (d[v] > d[u]) {
        int tmp = u;
        u = v;
        v = tmp;
    }
 
    if (u == v) return v;
 
    while (d[u] != d[v]) {
        int h = logs[d[u] - d[v]];
        u = dp[u][h];
    }
 
    if (v == u) {
        return v;
    }
    for (int i = log; i >= 0; --i) {
        if (dp[v][i] != dp[u][i]) {
            v = dp[v][i];
            u = dp[u][i];
        }
    }
 
    return dp[v][0];
}
 
int main() {
    int n, m;
    scanf("%d", &n);
    tree.resize(n);
    int t;
    while ((1 << log) <= n) {
        log++;
    }
 
    logs[0] = 0;
 
    for (int i = 1; i < n; ++i) {
        scanf("%d", &t);
        tree[t - 1].push_back(i);
        logs[i] = logs[i - 1];
        if (1 << (logs[i - 1] + 1) <= i) {
            ++logs[i];
        }
    }
 
    dfs(0, 0, 0);
    scanf("%d", &m);
 
 
    int u, v;
    for (int i = 0; i < m; ++i) {
 
        scanf("%d%d", &u, &v);
 
        printf("%d\n", lca(u - 1, v - 1) + 1);
    }
 
 
    return 0;
}
