#include <vector>
#include <fstream>
#include <iostream>
#include <climits>
#define vvll std::vector<std::vector<int>>
#define vll std::vector<int>

const static int INF = INT_MAX;
static size_t n;
const static size_t MAX_N = 302;

static int m[MAX_N][MAX_N], row[MAX_N], col[MAX_N];
static size_t M[MAX_N], way[MAX_N];

int main() {

    std::ifstream in("assignment.in");
    std::ofstream out("assignment.out");

    in >> n;
    size_t size = n + 1;

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            in >> m[i][j];
        }
    }


    for (size_t i = 1; i <= n; ++i) {
        M[0] = i; //number of row
        size_t free_col = 0;

        vll mins_col(size, INF);
        std::vector<bool> used(size, false);

        do {
            size_t adj_row = M[free_col];
            size_t new_col = 0;
            int delta = INF;

            used[free_col] = true; //visited

            for (size_t j = 1; j <= n; ++j) {
                if (!used[j]) {
                    int cur = m[adj_row][j] - row[adj_row] - col[j];
                    if (cur < mins_col[j]) {
                        mins_col[j] = cur;
                        way[j] = free_col;
                    }
                    if (mins_col[j] < delta) {
                        delta = mins_col[j];
                        new_col = j;
                    }
                }
            }

            for (size_t j = 0; j <= n; ++j) {
                if (used[j]) {
                    row[M[j]] += delta;
                    col[j] -= delta;
                } else mins_col[j] -= delta;
            }

            free_col = new_col;
        } while (M[free_col] != 0);

        do {
            int next = way[free_col];
            M[free_col] = M[next];
            free_col = next;
       } while (free_col != 0);
    }

    std::vector<size_t> answer(size);
    for (size_t i = 1; i <= n; ++i) {
        answer[M[i]] = i;
    }

    out << -col[0] << "\n";
    for (size_t i = 1; i <= n; ++i) {
        out << i << " " << answer[i] << "\n";
    }


    return 0;
}
