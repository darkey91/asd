#include <climits>
#include <cstdio>
#include <vector>
#include <iostream>
const int ZERO = INT_MAX;

int getMin(const std::vector <std::vector<int>> &st, const std::vector<int> &log, int l, int r) {
    int j = log[r - l + 1];
    return std::min(st[l][j], st[r - (1 << j) + 1][j]);
}

int getAns(const std::vector <std::vector<int>> &st, const std::vector<int> &log, int u, int v) {
    return getMin(st, log, std::min(u, v), std::max(u, v));
}


int main() {
    FILE *in, *out;
    in = fopen("sparse.in", "r");
    out = fopen("sparse.out", "w");

    int n, m, a1, u, v;
    fscanf(in, "%d%d%d%d%d", &n, &m, &a1, &u, &v);

    std::vector <std::vector<int>> st(n);
    std::vector<int> a(n), log(n + 1);
    log[1] = 0;

    for (int i = 2; i <= n; ++i) {
        log[i] = log[i - 1];
        if (1 << (log[i - 1] + 1) <= i) {
            ++log[i];
        }
    }

    a[0] = a1;
    st[0] = std::vector<int> (log[n] + 1);
    st[0][0] = a1;
    for (int i = 1; i < n; ++i) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
        st[i] = std::vector<int> (log[n] + 1);
        st[i][0] = a[i];
    }

    for (int j = 1; (1 << j) <= n; ++j) {
        int l = (1 << (j - 1));
        for (int i = 0; i + (1 << j) <= n; ++i) {
            st[i][j] = std::min(st[i][j - 1], st[i + l][j - 1]);
        }
    }
/*
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < log[n] + 1; ++j) {
            std::cout << st[i][j] <<" ";
        }
        std::cout << std::endl;
    }
*/
    int ans;

    for (int i = 1; i < m; ++i) {
        ans = getAns(st, log, u - 1, v - 1);
        u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
        v = ((13 * v + 593 + ans + 5 * i) % n) + 1;

    }

    ans = getAns(st, log, u - 1, v - 1);
    fprintf(out, "%d %d %d", u, v, ans);


    return 0;
}
