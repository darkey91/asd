#include <algorithm>
#include <fstream>
#include <map>
#include <vector>
#include <string>

const int MAX_N = 1000001;

class state {
public:
    state(int length = 0,int suf_link = 0): length(length), suf_link(suf_link) {}
    int length, suf_link;
    bool term = false;
    std::map<char, int> tr;
};

class suffix_automata {
public:
    suffix_automata() {
        state start;
        states.assign(2 * MAX_N, start);
        states[0].suf_link = -1;
        ++size;
        last = root = 0;
    }
    int amount(const std::string &t) {
        int cur = root;
        auto it = states[cur].tr.begin();

        for (size_t i = 0; i < t.size() && cur != -1; ++i) {
            it = states[cur].tr.find(t[i]);
            if (it == states[cur].tr.end()) return 0;
            cur = it->second;
        }
        return cnt[it->second];
    }



    void terminates(const std::string &s) {
        int cur = root;
        auto it = states[cur].tr.begin();
        cnt.assign(size, 0);
        for (size_t i = 0; i < s.size(); ++i) {
            it = states[cur].tr.find(s[i]);
            cur = it->second;
        }

        states[it->second].term = true;
        cnt[it->second] = 1;
        int p = states[it->second].suf_link;
        while (p >= 0) {
            if(p != 0) {
                states[p].term = true;
                cnt[p] = 1;
            }
            p = states[p].suf_link;
        }
        calculate_paths();
    }

    void build(const std::string &str) {
        for (char s: str) {
            int current = size++;
            states[current] .length = states[last].length + 1;

            int prev = last;
            while (prev >= 0 && states[prev].tr.find(s) == states[prev].tr.end()) {
                states[prev].tr.insert(std::make_pair(s, current));
                prev = states[prev].suf_link;
            }

            if (prev != -1) {
                int q = states[prev].tr.find(s)->second;
                if (states[prev].length + 1 == states[q].length) {
                    states[current].suf_link = q;
                } else {
                    int cl = clone(prev, q, s);
                    ++size;
                    states[current].suf_link = states[q].suf_link = cl;
                }
            }
            last = current;
        }
    }


    void calculate_paths() {
        used.assign(size, false);
        dfs(root);
    }
    int dfs(int v) {
        used[v] = true;
        for(auto &e: states[v].tr) {
            if(!used[e.second])
                cnt[v] += dfs(e.second);
            else cnt[v] += cnt[e.second];
        }
        return cnt[v];
    }
private:
    int clone(int p, int q, char c) {
        states[size] = states[q];
        states[size].length = states[p].length + 1;

        while (p >= 0 ) {
            auto it = states[p].tr.find(c);
            if (it->second != q) break;
            it->second = size;
            p = states[p].suf_link;
        }
        return size;
    }
    std::vector<bool> used;
    std::vector<int> cnt;
    std::vector<state> states;
    int size = 0, last, root;
};

int main() {
    std::ifstream in("search5.in");
    std::ofstream out("search5.out");

    int n;
    in >> n;

    std::vector<std::string> s;
    s.assign(MAX_N, "");
    std::string t;

    for (int i = 0; i < n; ++i) {
        in >> t;
        s[i] = t;
    }

    in >> t;

    suffix_automata sa;
    sa.build(t);
    sa.terminates(t);


    for (int i = 0; i < n; ++i) {
        out << sa.amount(s[i]) << std::endl;
    }


    return 0;
}