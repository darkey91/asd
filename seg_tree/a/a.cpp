#include <cstdio>
#include <algorithm>
#include <vector>

struct elem {
    long long data;
    long long sum;
};

long long sum(const std::vector<elem> &, int, int);

int main() {
    FILE *rFile, *wFile;
    rFile = fopen("sum0.in", "r");
    wFile = fopen("sum0.out", "w");

    long long ans = 0;

    long long n, x, y, a0, a_mod = 1 << 16;
    fscanf(rFile, "%lld%lld%lld%lld", &n, &x, &y, &a0);


    long long m, z, t, b0, b_mod = 1 << 30;
    fscanf(rFile, "%lld%lld%lld%lld", &m, &z, &t, &b0);

    if (n != 0 && m != 0) {
        std::vector<elem> a(n);
        std::vector<long long> b(m << 1, 0), c(m << 1, 0);

        b[0] = b0;
        c[0] = b[0] % n;

        for (int i = 1; i < b.size(); ++i) {
            b[i] = (z * b[i - 1] + t) % b_mod;
            if (b[i] < 0) {
                b[i] += b_mod;

            }
            c[i] = b[i] % n;

        }

        a[0].data = a0;
        a[0].sum = a0;

        for (int i = 1; i < n; ++i) {
            a[i].data = (x * a[i - 1].data + y) % a_mod;
            a[i].sum = a[i].data + a[i - 1].sum;

        }
        for (int i = 0; i < m; ++i) {
            int l = std::min(c[i << 1], c[(i << 1) + 1]);
            int r = std::max(c[i << 1], c[(i << 1) + 1]);
            ans += sum(a, l, r) + a[l].data;

        }
    }
    fprintf(wFile, "%lld", ans);
    return 0;
}


long long sum(const std::vector<elem> &a, int l, int r) {
    return a[r].sum - a[l].sum;
}