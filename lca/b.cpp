#include <vector>
#include <algorithm>
#include <climits>
#include <cstdio>
 
using namespace std;
 
vector<vector<pair<int, int>>> tree;
vector<vector<int>> dp, mins;
vector<int> logs;
int log = 1, n, timer = 0;
int depth[2 * int(1e5) + 10], tIn[2 * int(1e5) + 10], tOut[2 * int(1e5) + 10];
 
void dfs(int v, int p, int d) {
    dp[v][0] = p;
    depth[v] = d;
    tIn[v] = ++timer;
 
    for (int i = 1; i <= log; ++i) {
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
        mins[v][i] = min(mins[v][i - 1], mins[dp[v][i - 1]][i - 1]);
    }
 
    for (int i = 0; i < tree[v].size(); ++i) {
        int child = tree[v][i].first;
        dfs(child, v, d + 1);
    }
    tOut[v] = ++timer;
}
 
 
bool isParent(int child, int p) {
    return tIn[p] <= tIn[child] && tOut[child] <= tOut[p];
}
 
int lca(int u, int v) {
    if (isParent(u, v)) return v;
    if (isParent(v, u)) return u;
 
    for (int i = log; i >= 0; --i) {
        if (!isParent(v, dp[u][i])) {
            u = dp[u][i];
        }
    }
 
    return dp[u][0];
}
 
int get_min(int u, int v) {
    int l = lca(u, v);
    int d = depth[l];
    int ans = INT_MAX;
 
    if (l != u)
        ans = min(mins[u][0], ans);
    while (depth[u] != d) {
        int h = logs[depth[u] - d];
        ans = min(mins[u][h], ans);
        u = dp[u][h];
    }
 
    if (v != l)
        ans = min(mins[v][0], ans);
    while (depth[v] != d) {
        ans = min(mins[v][logs[depth[v] - d]], ans);
        v = dp[v][logs[depth[v] - d]];
    }
 
    return ans;
}
 
int main() {
    FILE *in, *out;
    in = fopen("minonpath.in", "r");
    out = fopen("minonpath.out", "w");
 
    fscanf(in, "%d", &n);
    while ((1 << log) <= n) {
        ++log;
    }
    tree.resize(n);
    dp.resize(n, vector<int>(log + 1));
    mins.resize(n, vector<int>(log + 1, INT_MAX));
    logs.resize(n + 1, 0);
    logs[0] = 0;
 
    int v, w, m;
    for (int i = 1; i < n; ++i) {
        fscanf(in, "%d%d", &v, &w);
        tree[v - 1].push_back(make_pair(i, w));
        logs[i] = logs[i - 1];
        mins[i][0] = w;
        if (1 << (logs[i - 1] + 1) <= i) {
            ++logs[i];
        }
    }
    if (1 << (logs[n - 1] + 1) <= n) ++logs[n];
 
    dfs(0, 0, 0);
    fscanf(in, "%d", &m);
 
    for (int i = 0; i < m; ++i) {
        fscanf(in, "%d%d", &v, &w);
        fprintf(out, "%d\n", get_min(v - 1, w - 1));
    }
    return 0;
}
