#include <queue>
#include <iostream>
#include <climits>

int S, T, N, M;

struct edge {
    int u, v, c, f;

    edge(int u, int v, int c = 0, int f = 0) : u(u), v(v), c(c), f(f) {}
};

bool bfs(const std::vector<std::vector<int>> &g, std::vector<edge> &edges, std::vector<int> &dist) {
    dist.assign(static_cast<size_t>(N), -1);
    dist[S] = 0;

    std::queue<int> q;
    q.push(S);

    while (dist[T] == -1 && !q.empty()) {
        int from = q.front();
        q.pop();
        for (int eFrom: g[from]) {
            int to = edges[eFrom].v;

            if (dist[to] == -1 && edges[eFrom].f < edges[eFrom].c) {
                q.push(to);
                dist[to] = dist[from] + 1;
            }
        }
    }

    return dist[T] != -1;
}

int dfs(std::vector<std::vector<int>> &g, std::vector<edge> &edges, std::vector<int> &dist, std::vector<int> &p,
        int v,
        int f) {
    if (!f)
        return 0;
    if (v == T)
        return f;

    for (; p[v] < (int) g[v].size(); ++p[v]) {
        int ev = g[v][p[v]];
        int to = edges[ev].v;

        if (dist[to] != dist[v] + 1) continue;
        int min = std::min(f, edges[ev].c - edges[ev].f);
        int toPush = dfs(g, edges, dist, p, to, min);
        if (toPush) {
            edges[ev].f += toPush;
            edges[ev + 1].f -= toPush;
            return toPush;
        }
    }


    return 0;
}


int main() {
    std::cin >> N >> M;
    S = 0;
    T = (int) N - 1;

    std::vector<edge> edges;
    std::vector<std::vector<int>> g(N, std::vector<int>());

    int u, v, capacity;
    for (size_t i = 0; i < M; ++i) {
        std::cin >> u >> v >> capacity;
        --u, --v;
        g[u].emplace_back((int) edges.size());
        edges.emplace_back(edge(u, v, capacity));

        g[v].emplace_back((int) edges.size());
        edges.emplace_back(edge(v, u));

        g[v].emplace_back((int) edges.size());
        edges.emplace_back(edge(v, u, capacity));

        g[u].emplace_back((int) edges.size());
        edges.emplace_back(edge(u, v));
    }

    std::vector<int> dist;
    std::vector<int> p;
    int flow = 0;

    while (true) {
        if (!(bfs(g, edges, dist)))
            break;
        p.assign(N, 0);

        while (int toPush = dfs(g, edges, dist, p, S, INT_MAX)) {
            flow += toPush;
        }
    }

    std::cout << flow << "\n";

    for (size_t i = 0; i < edges.size(); i += 4) {

        std::cout << edges[i].f + edges[i + 3].f << "\n";
    }

    return 0;
}
