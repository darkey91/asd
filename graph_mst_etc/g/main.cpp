#include <iostream>
#include <vector>
#include <map>

int n;
std::vector<bool> used;
std::vector<int> component;
int compCnt;

std::vector<std::vector<bool>> mat;

std::string getName(const std::string &s, int &index) {
    std::string name = "";
    int j = index + 1;
    for (; j < s.length() && s[j] != ' '; ++j) {
        name += s[j];
    }
    index = j;
    return name;
}

void addEdge(std::vector<std::vector<int>> &g, std::vector<std::vector<int>> &gT, const std::map<std::string, int> &names,
        const std::string &s) {
    int i = 0;
    int u, v, uNot, vNot;

    for (; s[i] != ' '; ++i) {
        if (s[i] == '+') {
            std::string nm = getName(s, i);
            u = names.find(nm)->second;
            uNot = u + n;
        } else if (s[i] == '-') {
            std::string nm = getName(s, i);
            uNot = names.find(nm)->second;
            u = uNot + n;
        }
    }
    for (; i < s.length(); ++i) {
        if (s[i] == '+') {
            std::string nm = getName(s, i);
            v = names.find(nm)->second;
            vNot = v + n;
        } else if (s[i] == '-') {
            std::string nm = getName(s, i);
            vNot = names.find(nm)->second;
            v = vNot + n;
        }
    }

    mat[u][v] = true;
    mat[vNot][uNot] = true;
    g[u].push_back(v);
    g[vNot].push_back(uNot);
    gT[v].push_back(u);
    gT[uNot].push_back(vNot);
}

void dfs(const std::vector<std::vector<int>> &g, std::vector<int> &top, int v) {
    used[v] = true;
    for (int u: g[v]) {
        if (!used[u]) {
            dfs(g, top, u);
        }
    }

    top.push_back(v);
}

void dfs(const std::vector<std::vector<int>> &g, int v) {
    component[v] = compCnt;
    for (int u: g[v]) {
        if (component[u] == -1)
            dfs(g, u);
    }
}

int main() {
    size_t m;
    std::cin >> n >> m;
    std::map<std::string, int> names;
    std::vector<int> top;
    std::vector<std::vector<int>> g(2 * n, std::vector<int>()), gT(2 * n, std::vector<int>());
    mat.assign((n << 1), std::vector<bool> ((n << 1), false));
    std::vector<std::string> nm;

    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        names.insert(std::make_pair(s, i));
        nm.push_back(s);
    }
    std::cin.ignore();
    for (int i = 0; i < m; ++i) {
        std::string s;
        std::getline(std::cin, s);
        addEdge(g, gT, names, s);
    }

    used.assign((n << 1), false);

    for (int i = 0; i < (n << 1); ++i) {
        if (!used[i])
            dfs(g, top, i);
    }

    component.assign((n << 1), -1);
    for (int i = (n << 1) - 1; i >= 0; --i) {
        if (component[top[i]] == -1) {
            dfs(gT, top[i]);
            ++compCnt;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (component[i] == component[i + n]) {
            std::cout << -1;
            return 0;
        }
    }

std::vector<int> l;

    for (int i = 0; i < n; ++i) {
        if (!mat[i][i + n]) {
            int ind = component[i] > component[i + n] ? i : i + n;
            if (ind < n) {
               l.push_back(ind);
            }
        }
    }
    std::cout << l.size() << "\n";
    for (int it: l) {
        std::cout << nm[it] << " ";
    }
    return 0;
}
