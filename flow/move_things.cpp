#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

static size_t N;
static const double EPS = 0.00001;
static const double INF = static_cast<double>(INT_MAX >> 1);
struct thing {
    double x, y, v;
    thing(double x, double y, double v) : x(x), y(y), v(v) {}
};

//s = v * t => t = s / v

struct place {
    double a, b;
    place (double a, double b) : a(a), b(b) {}
};

double evaluate_time(const thing & th, const place &pl) {
    return sqrt(pow(pl.a - th.x,  2) + pow(pl.b - th.y, 2))/ th.v;
}

void build_network(std::vector<std::vector<size_t>> &g, const std::vector<thing> &th, const std::vector<place> &pl, double time) {
    g.clear();
    g.assign(N, std::vector<size_t> ());

    for (size_t l = 0; l < N; ++l) {
        for (size_t r = 0; r < N; ++r) {
            if (evaluate_time(th[l], pl[r]) <= time)
                g[l].push_back(r);
        }
    }
}

bool dfs(std::vector<std::vector<size_t>> &g, std::vector<bool> &used, std::vector<int> &matching, size_t v) {
    if (used[v]) return false;
    used[v] = true;

    for (auto to: g[v]) {
        if (matching[to] == -1 || dfs(g, used, matching, static_cast<size_t>(matching[to]))) {
            matching[to] = static_cast<int>(v);
            return true;
        }
    }
    return false;
}

bool perfect_matching(const std::vector<thing> &things, const std::vector<place> &places, double time) {
    std::vector<std::vector<size_t>> g(N, std::vector<size_t> ());
    std::vector<int> matching(N, -1);
    std::vector<bool> used;

    build_network(g, things, places, time);
    for (size_t i = 0; i < N; ++i) {
        used.assign(N, false);
        dfs(g, used, matching, i);
    }

    for (auto l: matching) {
        if (l == -1) return false;
    }

    return true;
}

int main() {
    std::cin >> N;

    double x, y, v, a, b;
    std::vector<thing> things;
    std::vector<place> places;
    for (size_t i = 0; i < N; ++i) {
        std::cin >> x >> y >> v;
        things.push_back(thing(x, y, v));
    }

    for (size_t i = 0; i < N; ++i) {
        std::cin >> a >> b;
        places.push_back(place(a, b));
    }

    double l = 0, r = INF;

    while (r - l > EPS) {
        double mid = (r + l) / 2;
        if (perfect_matching(things, places, mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }

    std::cout << r;

    return 0;
}
