#include <queue>
#include <climits>
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

/*
4 5
A-.#-
...#-
--.--
--.-B
*/

static int SIZE, S, T, N, M;
const int INF = 1e6;
struct edge {
    bool isVer = false, isBack = false;
    int from, to;
    int c, f = 0, i = 0, j = 0;
    edge *back = nullptr;
    edge (int from, int to, int c = 0) : from(from), to(to), c(c) {}

};

void add_edge(std::vector<std::vector<edge *>> &g, int from, int to, int c, bool isVer, int i = -1, int j = -1) {
    edge *e1 = new edge (from, to, c), *e2 = new edge(to, from);
    e1->back = e2;
    e2->back = e1;
    e1->i = i;
    e1->j = j;
    e1->isVer = isVer;
    e2->isBack = true;
    g[from].push_back(e1);
    g[to].push_back(e2);
}

bool bfs(const std::vector<std::vector<edge *>> &g, std::vector<int> &dist) {
    dist.assign(SIZE, -1);
    dist[S] = 0;

    std::queue<int> q;
    q.push(S);

    while (dist[T] == -1 && !q.empty()) {
        int from = q.front();
        q.pop();
        for (auto e: g[from]) {
            int to = e->to;

            if (dist[to] == -1 && e->f < e->c) {
                q.push(to);
                dist[to] = dist[from] + 1;
            }
        }
    }

    return dist[T] != -1;
}

int dfs(std::vector<std::vector<edge *>> &g,  std::vector<int> &dist, std::vector<int> &p,
        int v,
        int f) {
    if (!f)
        return 0;
    if (v == T)
        return f;

    for (; p[v] < (int) g[v].size(); ++p[v]) {
        auto &e = g[v][p[v]];
        int to = e->to;

        if (dist[to] != dist[v] + 1) continue;
        int min = std::min(f, e->c - e->f);
        int toPush = dfs(g, dist, p, to, min);
        if (toPush) {
            e->f += toPush;
            e->back->f -= toPush;
            return toPush;
        }
    }


    return 0;
}

int find_max_flow(std::vector<std::vector<edge *>> &g, std::vector<int> &dist) {
       std::vector<int> p;
       int flow = 0;

       while (true) {
           if (!(bfs(g, dist)))
               break;

           p.assign(SIZE, 0);

           while (int toPush = dfs(g, dist, p, S, INF)) {
               flow += toPush;
           }
       }

    return flow;
}

bool is_valid(int i, int j) {
    return (i >= 0 && i < M && j >= 0 && j < N);
}

int get_number(int i, int j) {
    return (i * N + j) * 2;
}

int main() {
    std::cin >> M >> N;
    SIZE = N * M * 2;
    std::vector<std::vector<char>> t(M, std::vector<char> (N, '\0'));
    std::vector<std::vector<edge *>> g(SIZE, std::vector<edge *>());
    std::vector<std::pair<int, int>> step = {{0,-1}, {-1,0}, {0, 1}, {1,0}};

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            char c;
            std::cin >> c;
            t[i][j] = c;
            int ver = get_number(i,j);

            switch(c) {
            case 'A': {
                S = ver + 1;
                break;
            }
            case 'B':{
                T = ver;
                break;
            }
            case '-':{
               add_edge(g, ver, ver + 1, INF, true, i, j);
                break;
            }
            case'.': {
                add_edge(g, ver, ver + 1, 1, true, i, j);
                break;
            }
            case '#': {
                add_edge(g, ver, ver + 1, 0, true, i, j);
                break;
            }
            }
        }
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            for (auto &s: step) {
               int to_i = i+ s.first, to_j = j + s.second;

               if (is_valid(to_i, to_j) && t[to_i][to_j] != 'A') {
                        int to = get_number(to_i, to_j);
                        add_edge(g, get_number(i, j) + 1, to, INF, false);
               }
           }
        }
    }


    std::vector<int> dist;
    int flow = find_max_flow(g, dist);
    if (flow >= INF) {
        std::cout << -1;
        return 0;
    }
    std::cout << flow << '\n';

    for (int i = 0; i < g.size(); ++i) {
        if (i == S - 1) continue;
        for (auto &e: g[i]) {
            if (e->isVer && e->c != INF && e->f == 1) {
                if ((dist[get_number(e->i, e->j)] != -1 && dist[get_number(e->i, e->j) + 1] == -1 ) || (dist[get_number(e->i, e->j) + 1] != -1 && dist[get_number(e->i, e->j)] == -1 ))
                  t[e->i][e->j] = '+';
            }
        }
    }

    for (auto &str: t) {
        for (auto c: str) {
            std::cout << c;
        }
        std::cout << '\n';
    }

}

