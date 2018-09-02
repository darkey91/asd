#include <cstdio>
#include <vector>
#include <cstdlib>

int n, p = 1;
struct query {
    bool isBlack;
    int l;
    int r;
};

struct element {
    bool up = false;
    int left = 0;
    int right = 0;
    int segments = 0;
    int length = 0;
};

void push(std::vector<element> &t, int v) {
    if (t[v].up) {
        if ((v << 1) + 1 < n + p - 1) {
            t[(v << 1) + 1].up = true;
            t[(v << 1) + 1].length = t[v].length >> 1;
            t[(v << 1) + 1].left = t[v].left;
            t[(v << 1) + 1].right = t[v].left;
            t[(v << 1) + 1].segments = t[v].segments;
        }

        if ((v << 1) + 2 < n + p - 1) {
            t[(v << 1) + 2].up = true;
            t[(v << 1) + 2].length = t[v].length >> 1;
            t[(v << 1) + 2].left = t[v].left;
            t[(v << 1) + 2].right = t[v].right;
            t[(v << 1) + 2].segments = t[v].segments;
        }

        t[v].up = false;
    }
}


void update(std::vector<element> &t, int l, int r, int v, int tl, int tr, int isBlack) {
    if (l > tr || r < tl) {
        return;
    }

    if (l <= tl && r >= tr) {
        t[v].up = true;
        t[v].left = isBlack;
        t[v].right = isBlack;
        t[v].segments = isBlack;
        t[v].length = (tr - tl + 1) * isBlack;
        return;
    }
    push(t, v);

    int mid = (tl + tr) >> 1;
    update(t, l, r, (v << 1) + 1, tl, mid, isBlack);
    update(t, l, r, (v << 1) + 2, mid + 1, tr, isBlack);

    t[v].left = t[(v << 1) + 1].left;
    t[v].right = t[(v << 1) + 2].right;
    t[v].length = t[(v << 1) + 1].length + t[(v << 1) + 2].length;
    t[v].segments = t[(v << 1) + 1].segments + t[(v << 1) + 2].segments;
    if (t[(v << 1) + 1].right == 1 && t[(v << 1) + 2].left == 1) {
        t[v].segments -= 1;
    }
}

int main() {
    FILE *in, *out;
    in = fopen("painter.in", "r");
    out = fopen("painter.out", "w");
    int k;
    fscanf(in, "%d", &k);

    std::vector<query> q(k);

    char let;
    int left_x, right_x;
    fscanf(in, "%s%d%d", &let, &q[0].l, &q[0].r);

    q[0].isBlack = (let == 'B');
    left_x = q[0].l;
    right_x = q[0].l + q[0].r - 1;
    q[0].r = right_x;

    for (int i = 1; i < k; i++) {
        fscanf(in, "%s%d%d", &let, &q[i].l, &q[i].r);
        q[i].isBlack = (let == 'B');
        q[i].r = q[i].l + q[i].r - 1;

        if (q[i].l < left_x) {
            left_x = q[i].l;
        }

        if (q[i].r > right_x) {
            right_x = q[i].r;
        }
    }

    n = 1 - left_x + right_x;

    while (n > p) {
        p <<= 1;
    }
    std::vector<element> t(static_cast<unsigned long>((p << 1) - 1));

    for (int i = 0; i < k; ++i) {
        switch (q[i].isBlack) {
            case false: {
                update(t, q[i].l - left_x, q[i].r - left_x, 0, 0, p - 1, 0);
                fprintf(out, "%d %d\n", t[0].segments, t[0].length);

                break;
            }
            case true : {
                update(t, q[i].l - left_x, q[i].r - left_x, 0, 0, p - 1, 1);
                fprintf(out, "%d %d\n", t[0].segments, t[0].length);
                break;
            }

        }
    }


    return 0;
}