#include <cstdio>
#include <vector>
#include <climits>

using namespace std;

int N, p = 1;

int minimum(int a, int b) {
    if (a > b) return b;
    return a;
}

int maximum(int a, int b) {
    if (a < b) return b;
    return a;
}

struct area {
    bool isUpdated = false;
    int height = INT_MAX;

    void updateFromAbove(int new_data) {
        isUpdated = true;
        height = maximum(new_data, height);
    }

    void updateFromDown(int l, int r) {
        height = minimum(l, r);
    }
};

void push(std::vector<area> &tree, int v) {
    if (tree[v].isUpdated) {
        if ((v << 1) + 1 < N + p - 1)
            tree[(v << 1) + 1].updateFromAbove(tree[v].height);
        if ((v << 1) + 2 < N + p - 1)
            tree[(v << 1) + 2].updateFromAbove(tree[v].height);
        tree[v].isUpdated = false;
    }

}

void build(std::vector<area> &tree, int v, int l, int r) {
    if (l == r) {
        if (N + p - 1 > v) {
            tree[v].height = 0;
        }
        return;
    }
    int m = (l + r) >> 1;
    build(tree, (v << 1) + 1, l, m);
    build(tree, (v << 1) + 2, m + 1, r);
    tree[v].updateFromDown(tree[(v << 1) + 1].height, tree[(v << 1) + 2].height);

}

void update(std::vector<area> &tree, int v, int l, int r, int tl, int tr, int c) {
    if (l > tr || tl > r) {
        return;
    }
    if (tl >= l && tr <= r) {
        push(tree, v);
        tree[v].updateFromAbove(c);
        return;
    }
    push(tree, v);
    int m = (tl + tr) >> 1;

    update(tree, (v << 1) + 1, l, r, tl, m, c);
    update(tree, (v << 1) + 2, l, r, m + 1, tr, c);

    tree[v].updateFromDown(tree[(v << 1) + 1].height, tree[(v << 1) + 2].height);
}

int get(std::vector<area> &tree, int v, int l, int r, int tl, int tr) {
    if (l > tr || tl > r) {
        return INT_MAX;
    }

    if (tl >= l && tr <= r) {
        push(tree, v);
        return tree[v].height;
    }

    push(tree, v);

    int m = (tr + tl) >> 1;
    return minimum(
            get(tree, (v << 1) + 1, l, r, tl, m),
            get(tree, (v << 1) + 2, l, r, m + 1, tr)
    );
}

void find(const std::vector<area> &tree, int m, int v, int l, int r, int tl, int tr, int &ind) {
    if (l > tr || tl > r) {
        return;
    }

    if (tl >= l && tr <= r) {
        if (tree[v].height == m) {
            ind = v;
        }
        return;
    }
    int mid = (tl + tr) >> 1;
    find(tree, m, (v << 1) + 1, l, r, tl, mid, ind);
    find(tree, m, (v << 1) + 2, l, r, mid + 1, tr, ind);

}

int main() {
    int m;
    scanf("%d%d", &N, &m);

    char word[6];

    while (N > p) {
        p <<= 1;
    }

    std::vector<area> tree((p << 1) - 1);

    build(tree, 0, 0, p - 1);

    for (int i = 0; i < m; ++i) {
        scanf("%s6", &word);
        switch (word[0]) {
            case 'd' : {
                int a, b, c;
                scanf("%d%d%d", &a, &b, &c);
                update(tree, 0, a - 1, b - 1, 0, p - 1, c);
                break;
            }

            case 'a' : {
                int a, b, ans, index;
                scanf("%d%d", &a, &b);
                ans = get(tree, 0, a - 1, b - 1, 0, p - 1);
                find(tree, ans, 0, a - 1, b - 1, 0, p - 1, index);
                while (index < p - 1) {
                    push(tree, index);
                    int val = tree[(index << 1) + 1].height;

                    if (val == ans) {
                        index = (index << 1) + 1;
                    } else {
                        index = (index << 1) + 2;
                    }
                }
                printf("%d %d\n", ans, index - p + 2);
                break;
            }
        }
    }


    return 0;
}