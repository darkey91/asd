#include <climits>
#include <cstdio>
#include <vector>
#include <fstream>

int n, p;
long long neutralElem = LLONG_MAX;

struct ver {
    long long data = neutralElem;
    bool update = false;
    bool addition = false;
    long long new_data = 0;
    long long add = 0;
};

void build(std::vector<ver> &t, int v, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    build(t, (v << 1) + 1, l, mid);
    build(t, (v << 1) + 2, mid + 1, r);
    t[v].data = std::min(t[(v << 1) + 1].data, t[(v << 1) + 2].data);
}

void change(std::vector<ver> &t, int v) {
    if (t[v].update) {
        t[v].data = t[v].new_data;
    } else if (t[v].addition) {
        t[v].data += t[v].add;
    }

    t[v].add = 0;
    t[v].addition = false;
    t[v].update = false;
}

void change_child(std::vector<ver> &t, int v, int child) {
    if (child < n + p - 1) {
        if (t[v].update) {
            t[child].addition = false;
            t[child].update = true;
            t[child].new_data = t[v].new_data;
        } else if (t[v].addition) {
            if (t[child].update) {
                t[child].new_data += t[v].add;
            } else  {
                t[child].addition = true;
                t[child].add += t[v].add;
            }
        }
    }
}

void push(std::vector<ver> &t, int v) {
    change_child(t, v, (v << 1) + 1);
    change_child(t, v, (v << 1) + 2);
    change(t, v);
}

void update(std::vector<ver> &t, int v, int l, int r, int tl, int tr, long long data, bool up, bool addition) {
    if (l > tr || r < tl)
        return;

    if (l <= tl && tr <= r) {
        if (up) {
            t[v].update = true;
            t[v].addition = false;
            t[v].new_data = data;
            t[v].add = 0;

        } else {
            if (t[v].update) {
                t[v].add = 0;
                t[v].new_data += data;
            } else {
                t[v].addition = true;
                t[v].add += data;
            }
        }
        return;
    }

    push(t, v);

    int mid = (tl + tr) >> 1;
    update(t, (v << 1) + 1, l, r, tl, mid, data, up, addition);
    update(t, (v << 1) + 2, l, r, mid + 1, tr, data, up, addition);

    t[v].data = std::min((t[(v << 1) + 1].update) ? t[(v << 1) + 1].new_data : (t[(v << 1) + 1].addition) ? t[(v << 1) + 1].data + t[(v << 1) + 1].add : t[(v << 1) + 1].data,
                         (t[(v << 1) + 2].update) ? t[(v << 1) + 2].new_data : (t[(v << 1) + 2].addition) ? t[(v << 1) + 2].data + t[(v << 1) + 2].add : t[(v << 1) + 2].data);

}

long long get_min(std::vector<ver> &t, int l, int r, int v, int tl, int tr) {
    if (l > tr || tl > r) {
        return LLONG_MAX;
    }


    if (tl >= l && tr <= r) {
        return (t[v].update) ? t[v].new_data : (t[v].addition) ? t[v].data + t[v].add : t[v].data;
    }

    int mid = (tl + tr) >> 1;
    push(t, v);

    return std::min(
            get_min(t, l, r, (v << 1) + 1, tl, mid),
            get_min(t, l, r, (v << 1) + 2, mid + 1, tr)
    );
}

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("rmq2.in");
    out.open("rmq2.out");
    in >> n;

    p = 1;
    while (p < n) {
        p <<= 1;
    }
    std::vector<ver> t(static_cast<unsigned long>((p << 1) - 1));

    for (int i = p - 1; i < n + p - 1; ++i) {
        in >> t[i].data;
    }

    build(t, 0, 0, p - 1);

    std::string word;

    while (in >> word) {
        switch (word[0]) {
            case 's': {
                int l, r;
                long long data;
                in >> l >> r >> data;
                update(t, 0, --l, --r, 0, p - 1, data, true, false);
                break;
            }
            case 'a': {
                int l, r;
                long long data;
                in >> l >> r >> data;
                update(t, 0, --l, --r, 0, p - 1, data, false, true);

                break;
            }
            case 'm': {
                int l, r;
                in >> l >> r;
                long long ans = get_min(t, --l, --r, 0, 0, p - 1);
                out << ans << std::endl;
            }
        }
    }

    return 0;
}

