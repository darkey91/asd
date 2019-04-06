#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <iomanip>

double calcDist(std::pair<int, int> v, std::pair<int, int> u) {
    return sqrt(pow(v.first - u.first, 2) + pow(v.second - u.second, 2));
}

int main() {
    size_t n;
    std::cin >> n;
    double ans = 0;
    std::vector<std::pair<int, int>> vertex(n, std::pair<int, int>(0, 0));
    std::vector<double> d(n , double(INFINITY));
    std::vector<bool> used(n, false);

    std::vector <int> p(n, -1);

    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        vertex[i] = std::make_pair(x, y);

    }
    d[0] = 0;
    for (int i = 0; i < n; ++i) {
        int minV = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (minV == -1 || d[j] < d[minV])) {
                minV = j;
                //ans += d[j];
            }
        }
        used[minV] = true;

        if (p[minV] != -1) {
            ans += calcDist(vertex[minV], vertex[p[minV]]);
        }

        for (int v = 0; v < n; ++v) {
            double c = calcDist(vertex[minV], vertex[v]);
            if (c < d[v]) {
                d[v] = c;
                p[v] = minV;
            }

        }

    }

    std::cout << std::setprecision(9) << ans;

    return 0;
}