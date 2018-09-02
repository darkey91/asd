#include <stdio.h>
 
#include <algorithm>
#include <vector>
#include <climits>
#include <set>
 
using namespace std;
 
const int N = 2 * 100010, K = 18;
int tIn[N], log2[N], ind[N], st[N][K] = {INT_MAX};
int  timer = 0, n;
 
vector<vector<int>> tree;
 
vector<int> d(N, -1), arr;
 
int root;
 
 
void dfs(int v, int depth) {
    tIn[v] = ++timer;
    d[v] = depth;
    ind[v] = (int) arr.size();
    arr.push_back(v);
 
    for (auto to: tree[v]) {
        if (d[to] == -1) {
            dfs(to, depth + 1);
            arr.push_back(v);
 
        }
    }
 
}
 
int min_d(int i, int j) {
    return d[arr[i]] < d[arr[j]] ? i : j;
}
 
void build() {
    log2[1] = 0;
    for (int i = 2; i <= arr.size(); ++i) {
        log2[i] = log2[i - 1];
        if (1 << (log2[i - 1] + 1) <= i)
            ++log2[i];
    }
 
    for (int j = 0; (1 << j) <= arr.size(); ++j) {
        int l = (1 << (j - 1));
        for (int i = 0; i + (1 << j) <= arr.size(); ++i) {
            if (j == 0)
                st[i][0] = i;
            else
                st[i][j] = min_d(st[i][j - 1], st[i + l][j - 1]);
        }
    }
}
int getMin(int l, int r) {
    int j = log2[r - l + 1];
    return min_d(st[l][j], st[r - (1 << j) + 1][j]);
}
 
int getAns(int u, int v) {
    return getMin(std::min(u, v), std::max(u, v));
}
 
 
int lca(int u, int v) {
    u = ind[u];
    v = ind[v];
 
    int ans = getAns(u, v);
    return arr[ans];
}
 
 
int main() {
  //  ios::sync_with_stdio(false);
    int a, k, lords, l, prev = 0;
 
    scanf("%d", &n);
    tree.resize(n + 1, vector<int>());
 
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a);
        if (a == -1) root = i;
        else {
            tree[a].push_back(i);
        }
    }
 
    dfs(root, 1);
    build();
 
    scanf("%d", &k);
    int ans = 0;
    set<pair<int, int>> group;
    for (int i = 0; i < k; ++i) {
       scanf("%d", &lords);
 
        for (int j = 0; j < lords; ++j) {
            scanf("%d", &a);
            group.insert(make_pair(tIn[a], a));
        }
 
        for (auto v : group) {
            ans += d[v.second];
            if (prev != 0) {
                l = lca(prev, v.second);
                ans -= d[l];
            }
            prev = v.second;
        }
        prev = 0;
        printf("%d\n", ans);
        ans = 0;
        group.clear();
    }
    return 0;
}
