#include <stdio.h>
#include <array>
 
using namespace std;
const int N = 200020, K = 18;
int vertex = 1, dp[N][K + 1] = {1}, isEaten[N] = {false}, ancestor[N], d[N], logs[N], m;
 
 
int get_ancestor(int v) {
    return !isEaten[v] ? v : ancestor[v] = get_ancestor(ancestor[v]);
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
    for (int i = logs[m]; i >= 0; --i) {
        if (dp[v][i] != dp[u][i]) {
            v = dp[v][i];
            u = dp[u][i];
        }
    }
 
    return dp[v][0];
}
 
 
int main() {
    int p, r;
    char q;
    scanf("%d", &m);
 
    logs[1] = 0;
    for (int i = 1; i <= m; ++i) {
        logs[i] = logs[i - 1];
        if (1 << (logs[i - 1] + 1) <= i) {
            ++logs[i];
        }
    }
 
    for (int i = 0; i < m; ++i) {
        scanf("%s", &q);
        switch (q) {
            case '+' :{
                scanf("%d", &p);
                dp[++vertex][0] = p;
                d[vertex] = d[p] + 1;
                ancestor[vertex] = vertex;
                for (int i = 1; i <= K; ++i) {
                    dp[vertex][i] = dp[dp[vertex][i - 1]][i - 1];
                }
                break;
            }
            case '-' :{
                scanf("%d", &p);
                isEaten[p] = true;
                ancestor[p] = get_ancestor(dp[p][0]);
                break;
            }
            case '?' :{
                scanf("%d%d", &p, &r);
                int y = lca(p, r);
                int h = get_ancestor(y);
                printf("%d\n", get_ancestor(lca(p, r)));
                break;
            }
        }
 
    }
 
    return 0;
}
