#include <iostream>
#include <vector>
 
using namespace std;
int tIn[200009], tOut[200009];
int log = 1, timer = 0;
 
void dfs(const vector<vector<int>> &tree, vector<vector<int>> &dp, int v, int parent) {
    dp[v][0] = parent;
    tIn[v] = ++timer;
    for (int i = 1; i <= log; ++i) {
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
    }
    for (int i = 0; i < tree[v].size(); ++i) {
        int c = tree[v][i];
        if (c != parent) {
            dfs(tree, dp, c, v);
        }
    }
    tOut[v] = ++timer;
}
 
bool isParent(int child, int p) {
    return tIn[p] <= tIn[child] && tOut[child] <= tOut[p];
}
 
int lca(const vector<vector<int>> &dp, int u, int v) {
    if (isParent(u, v)) return v;
    if (isParent(v, u)) return u;
 
    for (int i = log; i >= 0; --i) {
        if (!isParent(v, dp[u][i])) {
            u = dp[u][i];
        }
    }
 
    return dp[u][0];
}
 
 
int main() {
    int n, m;
    cin >> n;
    vector<vector<int>> tree(n), dp(n);
 
    int t;
    while ((1 << log) <= n) {
        log++;
    }
 
    dp[0] = vector<int>(log + 1);
 
    for (int i = 1; i < n; ++i) {
        cin >> t;
        tree[t - 1].push_back(i);
        dp[i] = vector<int>(log + 1);
    }
 
    dfs(tree, dp, 0, 0);
    cin >> m;
 
    int u, v;
    for (int i = 0; i < m; ++i) {
 
        cin >> u >> v;
        cout << lca(dp, u - 1, v - 1) + 1 << endl;
    }
 
 
    return 0;
}
