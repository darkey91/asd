#include <cmath>
#include <vector>
#include <cstdio>
#include <complex>

int sum(const std::vector<int> &, int, int, int, int, int);

void update(std::vector<int> &, int, int, int);

int findK(const std::vector<int> &, int, int, int, int);

int main() {
    FILE *wFile, *rFile;
    wFile = fopen("parking.out", "w");
    rFile = fopen("parking.in", "r");

    int n, m;
    fscanf(rFile, "%d%d", &n, &m);

    int p = 1;
    while (p < n) {
        p <<= 1;
    }

    std::vector<int> a((p << 1) - 1);

    for (int i = p - 1; i < p - 1 + n; i++) {
        a[i] = 1;
    }

    for (int i = p - 2; i >= 0; i--) {
        a[i] = a[(i << 1) + 1] + a[(i << 1) + 2];
    }

    char key_word[5 + 1];

    for (int i = 0; i < m; i++) {
        fscanf(rFile, "%5s", &key_word);

        if (key_word[1] == 'n') {
            int place, ans;
            fscanf(rFile, "%d", &place);
            ans = --place;

            if (a[ans + p - 1] != 1) {
                int freePlaces = sum(a, 0, 0, p - 1, 0, place);
                ans = findK(a, 0, freePlaces + 1, 0, p - 1);

                if (ans < 0) {
                    ans = findK(a, 0, 1, 0, p - 1);
                }
            }


            update(a, ans, 0, p);
            fprintf(wFile, "%d\n", ++ans);

        } else {
            int place;
            fscanf(rFile, "%d", &place);
            update(a, place - 1, 1, p);
        }
    }
}

void update(std::vector<int> &a, int ind, int data, int p) {
    int v = ind + p - 1;
    a[v] = data;
    while (v != 0) {
        v = (v - 1) / 2;
        a[v] = a[(v << 1) + 1] + a[(v << 1) + 2];
    }
}

int sum(const std::vector<int> &a, int v, int tl, int tr, int l, int r) {
    if (l <= tl && r >= tr) {
        return a[v];
    }
    if (l > tr || r < tl) {
        return 0;
    }

    int mid = (tl + tr) / 2;
    return sum(a, (v << 1) + 1, tl, mid, l, r) + sum(a, (v << 1) + 2, mid + 1, tr, l, r);
}

int findK(const std::vector<int> &a, int v, int k, int l, int r) {
    if (k > a[v]) {
        return -1;
    }
    if (l == r) {
        return l;
    }

    int mid = (l + r) / 2;

    if (a[(v << 1) + 1] >= k) {
        return findK(a, (v << 1) + 1, k, l, mid);
    } else {
        return findK(a, (v << 1) + 2, k - a[(v << 1) + 1], mid + 1, r);
    }


}
