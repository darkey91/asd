#include <iostream>
#include <vector>
 
using namespace std;
 
const int N = int(1e6) + 3;
int tIn[N], tOut[N];
int log = 1, timer = 0;
vector<vector<int>> t, dp;
 
struct ver {
    int col;
    int amount = 1;
    int p;
};
 
void dfs( int v, int parent) {
    dp[v][0] = parent;
    tIn[v] = ++timer;
    for (int i = 1; i <= log; ++i) {
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
    }
    for (int i = 0; i < t[v].size(); ++i) {
        int c = t[v][i];
        if (c != parent) {
            dfs(c, v);
        }
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
 
ver vertexes[N];
int last[N] = {0};
 
void dfs1(int v, int p) {
    vertexes[v].p = p;
    if(last[vertexes[v].col] == 0) {
        last[vertexes[v].col] = v;
    } else {
          int l = lca(v, last[vertexes[v].col]);
        --vertexes[l].amount;
        last[vertexes[v].col] = v;
    };
    for (auto to: t[v]) {
        if (to == p) continue;
        dfs1(to, v);
        vertexes[v].amount += vertexes[to].amount;
    }
}
 
 
int main() {
    int n, root;
    cin >> n;
    while ((1 << log) <= n) {
        log++;
    }
    dp.resize(n + 1, vector<int>(log + 1));
    t.resize(n + 1);
 
    int p, col;
    for (int i = 1; i <= n; ++i) {
        cin >> p >> col;
        if (p == 0) root = i;
        t[p].push_back(i);
        vertexes[i].col = col;
    }
    dfs(root, root);
    dfs1(root, root);
 
    for (int i = 1; i <= n; ++i) {
        cout << vertexes[i].amount <<" ";
    }
 
    return 0;
}
