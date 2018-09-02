#include <iostream>
#include <vector>
 
#define pb push_back
 
using namespace std;
 
const long long N = 3 * int(1e5) + 5, K = 19;
long long par[N], tIn[N], tOut[N], s[N],
        wayLen[N] = {0}, wayOf[N], wayRoots[N], position[N], dp[N][K];
long long n, logN = 1, timer = 0, cnt = 0;
vector<vector<int>> t;
 
 
bool isParent(long long p, long long child) {
    return tIn[p] <= tIn[child] && tOut[child] <= tOut[p];
}
 
void dfs(long long v, long long p) {
    dp[v][0] = p;
    s[v] = 1;
    par[v] = p;
    tIn[v] = timer++;
 
    for (long long i = 1; i <= logN; ++i) {
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
    }
    for (auto to: t[v]) {
        if (to != p) {
            dfs(to, v);
            s[v] += s[to];
        }
    }
 
    tOut[v] = timer++;
}
 
long long newWay(long long v) {
    wayRoots[cnt] = v;
    return cnt++;
}
 
void build(long long v, long long wayNum) {
    wayOf[v] = wayNum;
    position[v] = wayLen[wayNum]++;
 
    for (auto to: t[v]) {
        if (to == par[v]) continue;
        if (2 * s[to] >= s[v]) {
            build(to, wayNum);
        } else {
            build(to, newWay(to));
        }
    }
 
}
 
 
long long lca(long long u, long long v) {
    if (isParent(v, u)) return v;
    if (isParent(u, v)) return u;
 
    for (long long i = logN; i >= 0; --i) {
        if (!isParent(dp[u][i],v)) {
            u = dp[u][i];
        }
    }
 
    return dp[u][0];
}
 
class fTree {
    long long n, *tree;
 
    void update(long long v, long long data) {
        while (v < n) {
            tree[v] += data;
            v = v | (v + 1);
        }
    }
 
public :
    void build(long long n) {
        this->n = n;
        tree = new long long[n]();
    }
 
    void update(long long u, long long v, long long data) {
        u = position[u];
        v = position[v];
        if (u > v) {
            long long temp = u;
            u = v;
            v = temp;
        }
 
        update(u, data);
        update(v + 1, -data);
    }
 
    long long get(long long v) {
        v = position[v];
        long long ans = 0;
        while (v >= 0 && (v & (v + 1)) >= 0) {
            ans += tree[v];
            v = (v & (v + 1)) - 1;
        }
        return ans;
    }
} ft[N];
 
 
 
void upd(long long u, long long v, long long data) {
    long long l = lca(u, v);
 
    while (wayOf[u] != wayOf[l]) {
        ft[wayOf[u]].update(u, wayRoots[wayOf[u]], data);
        u = par[wayRoots[wayOf[u]]];
    }
 
    while (wayOf[v]!= wayOf[l]) {
        ft[wayOf[v]].update(v, wayRoots[wayOf[v]], data);
        v = par[wayRoots[wayOf[v]]];
    }
 
    if (u != l && v == l) {
        ft[wayOf[u]].update(u, l, data);
    } else if (v != l && u == l) {
        ft[wayOf[v]].update(v, l, data);
    } else {
        ft[wayOf[l]].update(l, l, data);
    }
 
}
 
long long query(long long u) {
    return ft[wayOf[u]].get(u);
}
 
 
int main() {
    cin >> n;
    while ((1 << logN) <= n) {
        ++logN;
    }
 
    t.resize(n + 1, vector<int>());
    for (long long i = 1; i < n; ++i) {
        long long u, v;
        cin >> u >> v;
        t[u].pb(v);
        t[v].pb(u);
    }
 
    long long root = 1 + rand() % n;
    dfs(root, root);
    build(root, newWay(root));
 
    for (long long i = 0; i < cnt; ++i) {
        ft[i].build(wayLen[i]);
    }
 
 
    long long m, u, v, data;
    cin >> m;
    char q;
    for (long long i = 0; i < m; ++i) {
        cin >> q;
        switch (q) {
            case '?': {
                cin >> u;
                cout << query(u) << endl;
                break;
            }
            case '+': {
                cin >> u >> v >> data;
               upd(u, v, data);
            }
 
        }
    }
 
    return 0;
}
