#include <climits>
#include <iostream>
#include <vector>

static size_t  L, R;
static std::vector<int> matching;

bool dfs(std::vector<std::vector<size_t>> &g, std::vector<bool> &used, size_t v) {
  if (used[v]) return false;
  used[v] = true;

  for (auto u: g[v]) {
      if (matching[u] == -1 || dfs(g, used, static_cast<size_t>(matching[u]))) {
          matching[u] = static_cast<int> (v);
          return true;
      }
  }
  return false;
}

int main() {
    std::cin >> L >> R;
    std::vector<bool> used;

    std::vector<std::vector<size_t>> g(L, std::vector<size_t>());
    matching.assign(R, -1);

    size_t b;
    for (size_t a = 0; a < L; ++a) {
        while (true) {
            std::cin >> b;
            if (b == 0) break;
            g[a].push_back(b - 1);
        }
    }
    int matching_size = 0;

    for (size_t l = 0; l < L; ++l) {
        used.assign(L, false);
        matching_size += (dfs(g, used, l) ? 1 : 0);
    }

    std::cout << matching_size << "\n";

    for (size_t r = 0; r  < R; ++r) {
        if (matching[r] != -1)
            std::cout << matching[r] + 1 << " " << r + 1 << "\n";
    }
    return 0;
}
