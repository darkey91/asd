#include <queue>
#include <iostream>
#include <climits>

int N, M, S, T;

struct edge {
    bool min = false;
    int from, to;
    long long c, f;

    edge(int from, int to, long long c = 0, long long f = 0) : from(from), to(to), c(c), f(f) {}
};

bool bfs(std::vector<std::vector<int>> &g, std::vector<edge> &edges, std::vector<int> &dist) {
    dist.assign(N, -1);
    dist[S] = 0;

    std::queue<int> q;
    q.push(S);
    while (!q.empty() && dist[T] == -1) {
        int from = q.front();
        q.pop();

        for (auto eFrom: g[from]) {
            int to = edges[eFrom].to;
            if (dist[to] == -1 && edges[eFrom].c > edges[eFrom].f) {
                dist[to] = dist[from] + 1;
                q.push(to);
            }
        }
    }

    return dist[T] != -1;
}


long long dfs(std::vector<std::vector<int>> &g, std::vector<edge> &edges, std::vector<int> &dist,
        std::vector<int> &p, int v, long long flow) {
    if (!flow) return 0;
    if (v == T) return flow;

    for (; p[v] < g[v].size(); ++p[v]) {
        int eV = g[v][p[v]];
        int to = edges[eV].to;

        if (dist[to] == dist[v] + 1) {
            long long min = std::min(flow, edges[eV].c - edges[eV].f);
            long long to_push = dfs(g, edges, dist, p, to, min);

            if (to_push) {
                edges[eV].f += to_push;
                edges[eV + 1].f -= to_push;
                return to_push;
            }
        }
    }

    return 0;
}

int main() {
    std::cin >> N >> M;
    S = 0, T = N - 1;


    std::vector<std::vector<int>> g(N, std::vector<int>());
    std::vector<edge> edges;

    int v, u;
    long long c;

    for (int i = 0; i < M; ++i) {
        std::cin >> v >> u >> c;
        --v, --u;
        g[v].push_back((int) edges.size());
        edges.emplace_back(edge(v, u, c));

        g[u].push_back((int) edges.size());
        edges.emplace_back(edge(u, v));

        g[u].push_back((int) edges.size());
        edges.emplace_back(edge(u, v, c));

        g[v].push_back((int) edges.size());
        edges.emplace_back(edge(v, u));
    }

    std::vector<int> dist, p;
    long long flow = 0;

    while (true) {
        if (!bfs(g, edges, dist))
            break;

        p.assign(N, 0);

        long long to_push = 0;
        do {
            to_push = dfs(g, edges, dist, p, S, LONG_LONG_MAX);
            flow += to_push;
        } while (to_push != 0);

    }


    int min_cut_amount = 0;
    for (size_t i = 0; i < edges.size(); i += 4) {
        if ((dist[edges[i].from] != -1 && dist[edges[i].to] == -1) || (dist[edges[i + 2].from] != -1 && dist[edges[i + 2].to] == -1)) {
            ++min_cut_amount;
        }
    }

    std::cout << min_cut_amount << " " << flow << "\n";
    for (size_t i = 0; i < edges.size(); i += 4) {
        if ((dist[edges[i].from] != -1 && dist[edges[i].to] == -1) || (dist[edges[i + 2].from] != -1 && dist[edges[i + 2].to] == -1)) {
            std::cout << (i / 4) + 1 << " ";
        }
    }


    return 0;
}
