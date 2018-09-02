#include <cstdio>
#include <vector>
#include <array>
#include <iostream>

int mod;
std::array<int, 4> neutralElement{{1, 0, 0, 1}};

std::array<int, 4> mult(const std::array<int, 4> &a, const std::array<int, 4> &b) {
    std::array<int, 4> c;

    c[0] = (a[0] * b[0] + a[1] * b[2]) % mod;
    c[1] = (a[0] * b[1] + a[1] * b[3]) % mod;
    c[2] = (a[2] * b[0] + a[3] * b[2]) % mod;
    c[3] = (a[2] * b[1] + a[3] * b[3]) % mod;

    return c;
}

void build(std::vector<std::array<int, 4>> &a, int v, int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(a, (v << 1) + 1, l, mid);
    build(a, (v << 1) + 2, mid + 1, r);
    a[v] = mult(a[(v << 1) + 1], a[(v << 1) + 2]);
}

void print(const std::array<int, 4> &a, FILE *out) {
    fprintf(out, "%d %d\n%d %d\n", a[0], a[1], a[2], a[3]);
}

std::array<int, 4> get(const std::vector<std::array<int, 4>> &a, int l, int r, int v, int tl, int tr) {
    if (l > tr || r < tl) {
        return neutralElement;
    }
    if (tl >= l && r >= tr) {
        return a[v];
    }

    int mid = (tl + tr) >> 1;
    return mult(get(a, l, r, (v << 1) + 1, tl, mid), get(a, l, r, (v << 1) + 2, mid + 1, tr));
}

int main() {
    FILE *in, *out;
    in = fopen("crypto.in", "r");
    out = fopen("crypto.out", "w");

    int n, m;
    fscanf(in, "%d%d%d", &mod, &n, &m);
    int p = 1;
    while (n > p) {
        p <<= 1;
    }

    std::vector<std::array<int, 4>> A((p << 1) - 1);

    for (int i = p - 1; i < p - 1 + n; ++i) {
        std::array<int, 4> tmp;

        for (int j = 0; j < 4; ++j) {
            fscanf(in, "%d", &tmp[j]);
        }

        A[i] = tmp;
    }

    build(A, 0, 0, p - 1);
    for (int i = 0; i < m; ++i) {
        int l, r;
        fscanf(in, "%d%d", &l, &r);
        print(get(A, --l, --r, 0, 0, p - 1), out);
    }

    return 0;
}