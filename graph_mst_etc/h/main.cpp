#include <fstream>
#include <vector>
#include <climits>

using namespace std;
class DSU {
public:
    DSU(int n) {
        this->n = n;
        kings.assign(n, -1);
        rang.assign(n, 0);
    }

    void makeSet(int v) {
        kings[v] = v;
        ++rang[v];
    }
    void unionSets(int v, int u) {
        v = get(v);
        u = get(u);
    }
    int get(int v) {
        return (kings[v] ==  v) ? v : get(kings[v]);
    }

private:
    int n;
    std::vector<int> kings;
    std::vector<int> rang;
};

int main() {
    int ans = INT_MIN;
    ifstream in("avia.in");
    ofstream out("avia.out");
    int n;
    in >> n;
    vector<vector<int>> g(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> g[i][j];
        }
    }


    return 0;
}
