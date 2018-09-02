#include <fstream>
#include <vector>
#include <climits>
 
#define pb push_back
#define lc ((v << 1) + 1)
#define rc ((v << 1) + 2)
 
using namespace std;
 
const int N = 3 * int(1e5) + 5, K = 19;
int par[N], tIn[N], tOut[N], s[N], height[N],
        wayLen[N] = {0}, wayOf[N], wayRoots[N], position[N], dp[N][K];
int n, logN = 1, timer = 0, cnt = 0;
vector<vector<int>> t;
 
 
bool isParent(int p, int child) {
    return tIn[p] <= tIn[child] && tOut[child] <= tOut[p];
}
 
void dfs(int v, int p) {
    dp[v][0] = p;
    s[v] = 1;
    par[v] = p;
    tIn[v] = timer++;
 
    for (int i = 1; i <= logN; ++i) {
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
 
int newWay(int v) {
    wayRoots[cnt] = v;
    return cnt++;
}
 
void build(int v, int wayNum) {
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
 
int lca(int u, int v) {
    if (isParent(v, u)) return v;
    if (isParent(u, v)) return u;
 
    for (int i = logN; i >= 0; --i) {
        if (!isParent(dp[u][i], v)) {
            u = dp[u][i];
        }
    }
 
    return dp[u][0];
}
 
struct ver {
    int data = INT_MIN;
    int h;
    bool update = false;
};
 
class segTree {
    int n;
 
    void push(int v) {
        if (tree[v].update) {
            if (lc < n + p - 1) {
                tree[lc].h = tree[v].h;
                tree[lc].update = true;
            }
            if (rc < n + p - 1) {
                tree[rc].h = tree[v].h;
                tree[rc].update = true;
            }
            tree[v].update = false;
            tree[v].data = tree[v].h;
        }
    }
 
    void build1(int v, int l, int r) {
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build1((v << 1) + 1, l, mid);
        build1((v << 1) + 2, mid + 1, r);
        tree[v].data = max(tree[lc].data, tree[rc].data);
    }
 
public:
    ver *tree;
    int p = 1;
 
    void build(int n) {
        this->n = n;
        while (p < n) {
            p <<= 1;
        }
        tree = new ver[(p << 1) - 1];
    }
    void build() {
        build1(0, 0, p - 1);
    }
 
    void update(int v, int l, int r, int tl, int tr, int data) {
        if (l > tr || r < tl)
            return;
 
        if (l <= tl && tr <= r) {
            tree[v].update = true;
            tree[v].h = data;
            tree[v].data = data;
            return;
        }
 
        push(v);
 
        int mid = (tl + tr) >> 1;
        update(lc, l, r, tl, mid, data);
        update(rc, l, r, mid + 1, tr, data);
        tree[v].data = max(tree[lc].update ? tree[lc].h : tree[lc].data, tree[rc].update ? tree[rc].h : tree[rc].data);
    }
 
    int get(int v, int l, int r, int tl, int tr) {
        if (l > tr || tl > r) {
            return INT_MIN;
        }
 
 
        if (tl >= l && tr <= r) {
            int u = tree[v].data;
            return tree[v].data;
        }
 
        int mid = (tl + tr) >> 1;
        push(v);
 
        return max(
                get(lc,l, r,  tl, mid),
                get(rc,l, r,  mid + 1, tr)
        );
    }
 
} st[N];
 
 
void dfs1(int v, int p) {
    st[wayOf[v]].tree[position[v] + st[wayOf[v]].p - 1].data = height[v];
    for (auto to: t[v]) {
        if (to != p)
            dfs1(to, v);
    }
}
 
void upd(int u, int data) {
    st[wayOf[u]].update(0, position[u], position[u], 0, st[wayOf[u]].p - 1, data);
}
 
int query(int u, int v) {
    int ans = INT_MIN;
 
    int l = lca(u, v);
 
    while (wayOf[u] != wayOf[l]) {
        ans = max(ans, st[wayOf[u]].get(0, min(position[u], position[wayRoots[wayOf[u]]]),
                                        max(position[u], position[wayRoots[wayOf[u]]]), 0, st[wayOf[u]].p - 1));
        u = par[wayRoots[wayOf[u]]];
    }
 
    while (wayOf[v]!= wayOf[l]) {
        ans = max(ans, st[wayOf[v]].get(0, min(position[v], position[wayRoots[wayOf[v]]]),
                                        max(position[v], position[wayRoots[wayOf[v]]]), 0, st[wayOf[v]].p - 1));
        v = par[wayRoots[wayOf[v]]];
    }
 
    if (u != l && v == l) {
        ans = max(ans, st[wayOf[u]].get(0, min(position[l], position[u]),
                                        max(position[l], position[u]), 0, st[wayOf[l]].p - 1));
 
    } else if (v != l && u == l) {
        ans = max(ans, st[wayOf[v]].get(0, min(position[l], position[v]),
                                        max(position[v], position[l]), 0, st[wayOf[l]].p - 1));
    } else {
        ans = max(ans, st[wayOf[l]].get(0, position[l], position[l], 0, st[wayOf[l]].p - 1));
 
    }
 
    return ans;
}
 
 
int main() {
    ios::sync_with_stdio(false);
    ifstream in("mail.in");
    ofstream out("mail.out");
 
    in >> n;
    while ((1 << logN) <= n) {
        ++logN;
    }
 
    t.resize(n + 1, vector<int>());
    int h;
    for (int i = 1; i <= n; ++i) {
        in >> h;
        height[i] = h;
    }
    int u;
    for (int i = 1; i < n; ++i) {
        in >> h >> u;
        t[u].pb(h);
        t[h].pb(u);
    }
 
    int root = 1 + rand() % n;
    dfs(root, root);
    build(root, newWay(root));
 
    for (int i = 0; i < cnt; ++i) {
        st[i].build(wayLen[i]);
    }
 
    dfs1(root, root);
    for (int i = 0; i < cnt; ++i) {
        st[i].build();
    }
 
    int m, v, data;
    in >> m;
    char q;
    for (int i = 0; i < m; ++i) {
        in >> q;
        switch (q) {
            case '?': {
                in >> u >> v;
                out << query(u, v) << endl;
                break;
            }
            case '!': {
                in >> u >> data;
                upd(u, data);
            }
 
        }
    }
 
    return 0;
}
