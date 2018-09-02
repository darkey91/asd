#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>

int N, p = 1;

struct X {
    int x;
    bool isBegin;
    int up;
    int down;
};

struct Node {
    bool isUpdated = false;
    int data = INT_MIN;
    int addition = 0;
};

bool cmp(X x1, X x2) {
    return (x1.x < x2.x) || (x1.x == x2.x && (x1.isBegin || !x2.isBegin));
}

void build(std::vector<Node> &tree, int v, int l, int r) {
    if (l == r) {
        if (v < N + p - 1)
            tree[v].data = 0;
        return;
    }

    int mid = (l + r) >> 1;
    build(tree, (v << 1) + 1, l, mid);
    build(tree, (v << 1) + 2, mid + 1, r);
    tree[v].data = std::max(tree[(v << 1) + 1].data, tree[(v << 1) + 2].data);
}

void push(std::vector<Node> &tree, int v) {
    if (tree[v].isUpdated) {
        if ((v << 1) + 1 < N + p - 1) {
            if (tree[(v << 1) + 1].isUpdated) {
                tree[(v << 1) + 1].addition += tree[v].addition;
            } else {
                tree[(v << 1) + 1].isUpdated = true;
                tree[(v << 1) + 1].addition = tree[v].addition;
            }
        }
        if ((v << 1) + 2 < N + p - 1) {
            if (tree[(v << 1) + 2].isUpdated) {
                tree[(v << 1) + 2].addition += tree[v].addition;
            } else {
                tree[(v << 1) + 2].isUpdated = true;
                tree[(v << 1) + 2].addition = tree[v].addition;
            }
        }

        tree[v].isUpdated = false;
        tree[v].data += tree[v].addition;

    }
}

int get(std::vector<Node> &tree, int v, int l, int r, int tl, int tr) {
    if (l > tr || r < tl) {
        return INT_MIN;
    }

    if (tl >= l && r >= tr) {
        push(tree, v);
        return (tree[v].isUpdated ? tree[v].data + tree[v].addition : tree[v].data);
    }

    push(tree, v);

    int mid = (tl + tr) >> 1;
    return std::max(get(tree, (v << 1) + 1, l, r, tl, mid),
                    get(tree, (v << 1) + 2, l, r, mid + 1, tr));
}




void update(std::vector<Node> &tree, int v, int l, int r, int tl, int tr, int data) {
    if (l > tr || r < tl) {
        return;
    }
    if (l <= tl && r >= tr) {
        push(tree, v);
        if (tree[v].isUpdated) {
            tree[v].addition += data;

        } else {
            tree[v].isUpdated = true;
            tree[v].addition = data;
        }
        return;
    }

    push(tree, v);

    int mid = (tl + tr) >> 1;
    update(tree, (v << 1) + 1, l, r, tl, mid, data);
    update(tree, (v << 1) + 2, l, r, mid + 1, tr, data);
    tree[v].data = std::max(tree[(v << 1) + 1].isUpdated ?
                            tree[(v << 1) + 1].data + tree[(v << 1) + 1].addition : tree[(v << 1) + 1].data,
                            tree[(v << 1) + 2].isUpdated ?
                            tree[(v << 1) + 2].data + tree[(v << 1) + 2].addition : tree[(v << 1) + 2].data
    );
}

int _y(std::vector<Node> &tree) {
    int max = tree[0].data;
    int v = 0;
    while ((v << 1) + 1 < N + p - 1) {
        push(tree, v);
        int leftChild = tree[(v << 1) + 1].isUpdated ? tree[(v << 1) + 1].addition + tree[(v << 1) + 1].data : tree[
                (v << 1) + 1].data;
        if (leftChild == max) {
            v = (v << 1) + 1;
        } else {
            v = (v << 1) + 2;
        }
    }
    return v;
}

int main() {
    int n;
    scanf("%d", &n);

    std::vector<X> _x(n << 1);

    int y_min, y_max;

    scanf("%d%d%d%d", &_x[0].x, &_x[0].up, &_x[1].x, &_x[0].down);

    _x[0].isBegin = true;
    _x[1].isBegin = false;
    _x[1].up = _x[0].up;
    _x[1].down = _x[0].down;

    y_min = _x[0].up;
    y_max = _x[0].down;

    for (int i = 2; i < (n << 1); i += 2) {
        scanf("%d%d%d%d", &_x[i].x, &_x[i].up, &_x[i + 1].x, &_x[i].down);
        _x[i].isBegin = true;
        _x[i + 1].isBegin = false;
        _x[i + 1].up = _x[i].up;
        _x[i + 1].down = _x[i].down;

        if (y_min > _x[i].up) {
            y_min = _x[i].up;
        }
        if (y_max < _x[i].down) {
            y_max = _x[i].down;
        }
    }

    std::sort(_x.begin(), _x.end(), cmp);

    N = 1 - y_min + y_max;

    while (N > p) {
        p <<= 1;
    }


    std::vector<Node> tree((p << 1) - 1);

    build(tree, 0, 0, p - 1);

    int ans, x_ans, y_ans;
    int move = 0 - y_min;

    int add_value = _x[0].isBegin ? 1 : -1;

    update(tree, 0, _x[0].up + move, _x[0].down + move, 0, p - 1, add_value);


    ans = tree[0].data;
    x_ans = _x[0].x;
    y_ans = _x[0].up;

    for (int i = 1; i < _x.size(); ++i) {
        add_value = _x[i].isBegin ? 1 : -1;
        update(tree, 0, _x[i].up + move, _x[i].down + move, 0, p - 1, add_value);

        if (ans < tree[0].data) {
            ans = tree[0].data;
            x_ans = _x[i].x;
            y_ans = _y(tree) - move - p + 1;
        }

    }

    printf("%d\n%d %d", ans, x_ans, y_ans);
    return 0;
}