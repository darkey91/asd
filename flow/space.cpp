#include <assert.h>
#include <sstream>
#include <iostream>
#include <queue>
#include <climits>
#include <fstream>
#include <vector>

struct edge {
    size_t from, to;
    long long c, f = 0;
    edge * back;
    edge(size_t from, size_t to, long long c = 0) : from(from), to(to), c(c) {}
};

static size_t N, M, K, S, T, N_MAX;
static const size_t DAY_MAX = 50 * 200;

void add_edge(std::vector<std::vector<edge *>> &g, size_t from, size_t to, long long c) {
    edge *e1 = new edge(from, to, c), *e2 = new edge(to, from);
    e1->back = e2;
    e2->back = e1;
    g[from].push_back(e1);
    g[to].push_back(e2);
}

void build_graph(std::vector<std::vector<edge *>> &g, const std::vector<std::pair<size_t, size_t>> &edges,
                 size_t DAY) {

    for (size_t i = 0; i < N; ++i) {
        add_edge(g, i + (DAY - 1) * N, i + DAY  * N, INT_MAX);
    }

    for (size_t i = 0; i < M; ++i) {
        add_edge(g, edges[i].first + (DAY - 1) * N, edges[i].second + DAY * N, 1);
        add_edge(g, edges[i].second + (DAY - 1) * N, edges[i].first + DAY * N, 1);
    }

}

bool bfs(const std::vector<std::vector<edge *>> &g, std::vector<int> &dist, size_t day) {
    dist.assign((day + 1) * N, -1);
    dist[S] = 0;
    std::queue<size_t> q;
    q.push(S);

    while (!q.empty() && dist[T] == -1) {
        size_t v = q.front();
        q.pop();
        for (auto &e: g[v]) {
            size_t to = e->to;
            if (dist[to] == -1 && e->c > e->f) {
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }
    return dist[T] != -1;
}

long long update_flow(std::vector<std::vector<edge *>> &g, std::vector<size_t> &p, std::vector<int> &dist, size_t v, long long add) {
    if (v == T || add == 0) return add;

    long long f = 0;
    for (; p[v] < g[v].size(); ++p[v]) {
        edge *e = g[v][p[v]];
        size_t to = e->to;
        if ((dist[to] == (dist[v] + 1)) && e->c > e->f) {
            long long push = update_flow(g, p, dist, to, std::min(add, e->c - e->f));
            if (push > 0) {
                e->f += push;
                e->back->f -= push;
                return push;
            }
        }
    }
    return 0;

}

long long dinic(std::vector<std::vector<edge *>> &g, size_t day, long long left) {
    std::vector<int> dist;
    long long flow = 0;
    std::vector<size_t> p;

    while (true) {
        if (!bfs(g, dist, day)) break;
        p.assign(N_MAX, 0);
        flow += update_flow(g, p, dist, S, left - flow);
        if (left == flow) break;
    }
    return flow;
}

long long dfs(std::vector<std::vector<edge *>> &g,  std::vector<bool> &used, size_t v, long long flow) {
    if (v == T) return flow;

    used[v] = true;

    for (auto &e:g[v]) {
        size_t to = e->to;

        if (!used[to] && e->c > e->f) {
            long long to_push = dfs(g, used, to, std::min(flow, e->c - e->f));
            if (to_push > 0) {
                e->f += to_push;
                e->back->f -= to_push;
                return to_push;
            }
        }
    }
    return 0;
}

long long find_max_flow(std::vector<std::vector<edge *>> &g, long long left, size_t day) {
    long long flow = 0;
    std::vector<bool> used;

    while (true) {
        used.assign((day + 1) * N, false);
        long long pushed = dfs(g, used, S, left - flow);

        if (pushed == 0) break;
        flow += pushed;

        if (flow == left) break;
    }
    return flow;
}

int main() {
    std::ifstream in("bring.in");
    std::ofstream out("bring.out");
    
    in >> N >> M >> K >> S >> T;
    --S;
    --T;

    N_MAX = DAY_MAX * N;

    size_t TERMINAL = T;
    std::vector<std::vector<edge *>> g(N_MAX, std::vector<edge *>());

    std::vector<std::pair<size_t, size_t>> edges;

    size_t from, to;
    for (size_t i = 0; i < M; ++i) {
        in >> from >> to;
        edges.push_back({--from, --to});
    }

    size_t day = 1;
    long long cnt = 0;
    while (cnt != K) {
       build_graph(g, edges, day);
       T = day * N + TERMINAL;
     //  cnt += dinic(g, day, K- cnt);
      cnt += static_cast<size_t>(find_max_flow(g, static_cast<long long>(K - cnt), day));
      assert(cnt <= K);

       ++day;
    }

    out << --day << "\n";

    std::vector<long long> ships(K + 1, S + 1);

    for (size_t d = 0; d < day; ++d) {
        std::vector<std::pair<size_t, size_t>> tunnel;
        for (size_t i = 0; i < N; ++i)

            for (auto &e: g[d * N + i]) {
                if (e->c != INT_MAX && e->f == 1) {
                    tunnel.push_back({e->from % N + 1, e->to % N + 1});
                }
            }

        out << tunnel.size() << " ";
        std::vector<bool> used(K + 1, false);

        for (auto t: tunnel) {
            for (size_t sh = 1; sh <= K; ++sh) {
                if (!used[sh] && ships[sh] == t.first) {
                    out << sh << " " << t.second << " ";
                    ships[sh] = t.second;
                    used[sh] = true;
                    break;
                }
            }
        }
        out << "\n";

    }


    return 0;
}
