#include <climits>
#include <vector>
#include <iostream>
static size_t N, W;
static size_t S = 0, T;

long long INF = INT_MAX;

struct thing {
    int x1, y1,x2,y2;
    thing(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};

long long get_dist(const thing &lhs, const thing &rhs) {
    long long x = std::max(lhs.x1 - rhs.x2, rhs.x1 - lhs.x2);
    long long y = std::max(lhs.y1 - rhs.y2, rhs.y1 - lhs.y2);
    return (x > 0 || y > 0) ? std::max(x, y) : 0;
}
long long dijkstra(const std::vector<std::vector<long long>> &g) {
    std::vector <long long> dist(N + 2, INF);

    std::vector<long long> used(N+2, false);
    dist[S] = 0;

    for (size_t i = 0; i < dist.size(); ++i) {
        int v = -1;
        for (size_t j = 0; j < dist.size(); ++j) {
            if (!used[j] && (v == -1 || dist[j] < dist[v])) {
                v = j;
            }
        }
        if (dist[v] == INF) break;
        used[v] = true;

        for (size_t j = 0; j < dist.size(); ++j) {
            if (j != v && dist[j] > dist[v] + g[v][j]) {
                    dist[j] = dist[v] + g[v][j];
                }
            }
        }
        return dist[T];
}


int main() {
    std::cin >> N >> W;
    std::vector<thing> things;

    std::vector<std::vector<long long>> g(N + 2, std::vector<long long> (N + 2, 0));
    T = N + 1;

    g[S][T] = W;
    g[T][S] = W;

    int x1, y1, x2, y2;
    for (size_t i = 1; i <= N; ++i) {
        std::cin >> x1 >> y1 >> x2 >> y2;
        things.push_back(thing(x1,y1,x2,y2));
        g[S][i] = W -  y2;
        g[i][S] = W -  y2;
        g[T][i] = y1;
        g[i][T] = y1;
    }


    for (size_t i = 1; i <= N; ++i) {
        for (size_t j = i + 1; j <= N; ++j) {
                g[i][j] = g[j][i] = get_dist(things[i - 1], things[j - 1]);
        }
    }
    long long ans = dijkstra(g);

    std::cout << (ans == INF ? 0 : ans);
    return 0;
}
