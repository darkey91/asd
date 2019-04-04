#include <assert.h>
#include <unordered_map>
#include <queue>
#include <climits>
#include <memory>
#include <iostream>
#include <vector>

static size_t N, S = 0, T = 0, SIZE = 1;
static int W = 3, w = 2, l = 1;

struct edge {
    size_t from, to;
    int c, f;
    edge* back;
    size_t a = 0, b = 0;
    edge(size_t from, size_t to, int c = 0)
        : from(from)
        , to(to)
        , c(c)
    {

    }

};

int dfs(std::vector<std::vector<edge *>> &g,  std::vector<bool> &used, size_t v, int flow) {
    if (v == T) return flow;

   used[v] = true;

    for (auto &e:g[v]) {
        size_t to = e->to;

        if (!used[to] && e->c > e->f) {
            int to_push = dfs(g, used, to, std::min(flow, e->c - e->f));
            if (to_push > 0) {
                e->f += to_push;
                e->back->f -= to_push;
                return to_push;
            }
        }
    }
    return 0;
}

int find_max_flow(std::vector<std::vector<edge *>> &g) {
    int flow = 0;
    std::vector<bool> used;

    while (true) {
        used.assign(SIZE, false);
        int pushed = dfs(g, used, S, INT_MAX);

        if (pushed == 0) break;
        flow += pushed;
    }
    return flow;
}

void add_edge(std::vector<std::vector<edge*> >& g, size_t from, size_t to, int c, size_t a = 0, size_t b = 0)
{
    edge *e1 = new edge(from, to, c), *e2 = new edge(to, from);
    e1->back = e2;
    e2->back = e1;
    e1->a = a;
    e1->b = b;
    g[from].push_back(e1);
    g[to].push_back(e2);
}

bool valid(size_t i) {
    return i >= 1 && i <= N;
}

bool check(const std::vector<std::vector<char>> &table) {
    for (size_t i = 1; i <= N; ++i) {
        for (size_t j = 1 + i; j <= N; ++j) {
            char expected = '?';

            switch(table[i][j]) {
                case 'l': {
                    expected = 'w';
                    break;
                }
                case 'w': {
                    expected = 'l';
                    break;
                }
                case 'W': {
                    expected = 'L';
                    break;
                }
                case 'L' :{
                    expected = 'W';
                    break;
                }
            }
            if (expected != table[j][i]) {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    std::cin >> N;

   SIZE = N + 2 + ((N - 1) * (N - 1) + N - 1) / 2;

    T = SIZE - 1;

    std::vector<std::vector<char> > table(N + 1, std::vector<char>(N + 1, '\0'));
    std::vector<std::vector<edge*> > g(SIZE, std::vector<edge *>());
    std::vector<std::pair<size_t, size_t> > p;

    std::vector<size_t> points(N + 1, 0);
    char s;
    for (size_t i = 1; i <= N; ++i) {
        for (size_t j = 1; j <= N; ++j) {

            std::cin >> s;
            table[i][j] = s;

            if (j > i) {
                switch (s) {
                case 'W': {
                    points[i] += W;
                    break;
                }
                case 'w': {
                    points[i] += w;
                    points[j] += l;
                    break;
                }
                case 'l': {
                    points[i] += l;
                    points[j] += w;
                    break;
                }
                case 'L': {
                    points[j] += W;
                    break;
                }
                case '.': {
                    p.push_back({i, j});
                    break;
                }
                }
            }
        }
    }

    size_t last_ver = N;

    for (size_t i = 1; i <= N; ++i) {
        int c;
        std::cin >> c;
        c -= points[i];
        add_edge(g, S, i, c);
    }

   for (auto &pair: p) {
       ++last_ver;
       add_edge(g, pair.first, last_ver, W);
       add_edge(g, pair.second, last_ver, W);
       add_edge(g, last_ver, T, W);
   }

    find_max_flow(g);

    for (size_t i = 1; i <= N; ++i) {
        for (auto &e: g[i]) {
            if (valid(e->a) && valid(e->b)) {
               char s = '?';
               switch (e->f) {
               case 0: {
                   s = 'L';
                   break;
               }
               case 1: {
                   s = 'l';
                   break;
               }
               case 2: {
                   s = 'w';
                   break;
               }
               case 3: {
                   s = 'W';
                   break;
               }
               }
               table[e->a][e->b] = s;
            }
        }
    }


    for (size_t i = 1; i <= N; ++i) {
        for (size_t j = 1; j <= N; ++j) {
            std::cout << table[i][j] ;
        }
        std::cout << "\n";
    }


    return 0;
}
