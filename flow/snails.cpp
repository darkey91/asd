#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>

static size_t S, T, N, M;

struct edge {
    bool used = false;
    size_t from, to;
    int c = 0, f = 0;
    edge * back;
    edge(size_t from, size_t to, int c = 0) : from(from), to(to), c(c) {}
};

int dfs(std::vector<std::vector<edge *>> &g, std::vector<bool> &used, size_t v, int flow) {
    if (v == T || flow == 0)
        return flow;

    used[v] = true;

    for (auto &e: g[v]) {
        size_t to = e->to;
        if (!used[to] && e->c > e->f) {
            int min = std::min(flow, e->c - e->f);
            int to_push = dfs(g, used, to, min);
            if (to_push > 0) {
                e->f += to_push;
                e->back->f -= to_push;
                return to_push;
            }
        }
    }
    return 0;
}

void print_path(std::vector<std::vector<edge *>> &g, std::vector<bool> &used, size_t v) {
    if (v == T) return;

    std::cout << v + 1 << " ";
    used[v] = true;
    for (auto &e: g[v]) {
        size_t to = e->to;
        if (!e->used && e->f == 1 && !used[to]) {
            e->used = true;
            print_path(g, used, to);
            break;
        }
    }
}

void add_edge (std::vector<std::vector<edge *>> &g, size_t from, size_t to) {
    edge *e1 = new edge(from, to, 1);
    edge *e2 = new edge(to, from);

    e1->back = e2;
    e2->back = e1;
    g[from].push_back(e1);
    g[to].push_back(e2);
}

int main() {
    std::cin >> N >> M >> S >> T;
    --S;
    --T;

    size_t from, to;

    std::vector<std::vector<edge *>> g( N, std::vector<edge *>());

    for (size_t i = 0; i < M; ++i) {
        std::cin >> from >> to;
        --from;
        --to;
        if (to != from) {
            add_edge(g, from, to);
        }
    }

    std::vector<bool> used;
    used.assign(N, false);

    int pushed1 = dfs(g, used, S, INT_MAX);
    if (pushed1 == 0) {
        std::cout << "NO";
        return 0;
    }

    used.assign(N, false);
    int pushed2 = dfs(g,  used, S, INT_MAX);

    if (pushed1 + pushed2 < 2) {
        std::cout << "NO";
    } else {
        std::cout << "YES\n";

        used.assign(N, false);
        print_path(g, used, S);
        std::cout << T + 1 << "\n";

        used.assign(N, false);
        print_path(g, used, S);
        std::cout << T + 1 << "\n";
    }

    return 0;
}
