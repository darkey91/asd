#include <iostream>
#include <map>
#include <queue>
#include <climits>
#include <fstream>
#include <vector>

static size_t n, m, S = 0, T, size;

const long long INF = LLONG_MAX;

struct edge {
    size_t from, to;
    long long w, c, f = 0;
    edge  *back = nullptr;
    edge(size_t from, size_t to, long long w, long long c = 0) : from(from), to(to), w(w), c(c) {}
};

void add_edge(std::vector<std::vector<size_t>> &g, std::vector<edge *> &edges, size_t from, size_t to, long long c, long long w) {
    edge *a = new edge(from, to, w, c), *b = new edge(to, from, -w);
    a->back = b;
    b->back = a;
    g[from].push_back(edges.size());
    edges.push_back(a);
    g[to].push_back(edges.size());
    edges.push_back(b);
}


bool dij(std::vector<std::vector<size_t>> &g, std::vector<edge *> &edges, std::vector<long long> &p) {
    p.assign(size, -1);
    std::vector<bool> used(size, false);

    std::vector<long long> distance(size, LLONG_MAX);
    distance[S] = 0;

    std::multimap<long long, size_t> dist;
    dist.insert({0,0});

    while (!dist.empty()) {
        auto min = *dist.begin();
        dist.erase(dist.begin());

        for (size_t j = 0; j < g[min.second].size(); ++j) {
            size_t e = g[min.second][j];
            size_t to = edges[e]->to;
            if (edges[e]->c - edges[e]->f > 0 && distance[min.second] + edges[e]->w < distance[to]) {
                distance[to] = distance[min.second] + edges[e]->w;
                dist.insert({distance[to], to});
                p[to] = e;
            }
        }
    }
    return distance[T] != LLONG_MAX;
}

int main() {

    std::cin >> n >> m;
    size = 2 * n + 2;
    T = size - 1;

    std::vector<std::vector<size_t>> g(size, std::vector<size_t>());
    std::vector<edge *> edges;

    std::vector<long long> visa(size, 0);

    for (size_t i = 1; i <= n; ++i) {
        std::cin >> visa[i];
        add_edge(g, edges, S, i, 1, 0);
        add_edge(g, edges, i, n + i, INF, visa[i]);
        add_edge(g, edges, n + i, i, INF, 0);
        add_edge(g, edges, n + i, T, 1, 0);
    }

    size_t from, to;
    long long w;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> from >> to >> w;
        add_edge(g, edges, from, n + to, INF, w);
    }

    std::vector<long long> p;
    long long cost = 0;

    while(dij(g, edges, p)) {
        size_t cur = T;
        long long f = INF;

        while (cur != S) {
            f = std::min(f, edges[p[cur]]->c - edges[p[cur]]->f);
            cur = edges[p[cur]]->from;
        }

        cur = T;

        while (cur != S) {
            edges[p[cur]]->f += f;
            edges[p[cur]]->back->f -= f;
            cost += f * edges[p[cur]]->w;
            cur = edges[p[cur]]->from;
        }
    }

    std::cout << cost;

    return 0;
}
