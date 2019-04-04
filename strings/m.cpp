#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>
class state {
public:
    state(int length = 0,int suf_link = 0): length(length), suf_link(suf_link) {}
    int length, suf_link;
    std::map<char, int> tr;
};

class suffix_automata {
public:
    suffix_automata() {
        states.emplace_back(state(0, -1));
        ++size;
        last = root = 0;
    }
    bool accept(const std::string &t) {
        int cur = root;
        for (size_t i = 0; i < t.size() && cur != -1; ++i) {
            auto it = states[cur].tr.find(t[i]);
            if (it == states[cur].tr.end()) return false;
            cur = it->second;
        }
        return true;
    }
    void build(const std::string &str) {

        for (char s: str) {
            int current = size++;
            states.emplace_back(state(states[last].length + 1));

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
                    states[current].suf_link = states[q].suf_link = cl;
                }
            }
            last = current;
        }
    }

    void find_lcs(const std::string &s, const std::string &t, std::string &lcs) {
        int current = 0, len = 0, b = 0, e = 0;
        for (int i = 0; i < (int)t.size(); ++i) {
            while (current >= 0 && states[current].tr.find(t[i]) == states[current].tr.end()) {
                current = states[current].suf_link;
                len = states[current].length;
            }

            if (states[current].tr.count(t[i])) {
                current = states[current].tr.find(t[i])->second;
                ++len;
            }

            if (len > b) {
                b = len;
                e = i;
            }
        }
        lcs = t.substr(e - b + 1, b);

    }
private:
    int clone(int p, int q, char c) {
        ++size;
        states.emplace_back(states[q]);
        states.back().length = states[p].length + 1;

        while (p >= 0 && states[p].tr.find(c)->second == q) {
            states[p].tr.find(c)->second = static_cast<int> (states.size() - 1);
            p = states[p].suf_link;
        }

        return static_cast<int> (states.size() - 1);
    }

    std::vector<state> states;
    int size = 0, last, root;
};

int main() {
    std::ifstream in("common.in");
    std::ofstream out("common.out");
    std::string s, t;
    in >> s >> t;

    std::string lcs;
    suffix_automata sa;
    if (s.size() < t.size()) swap(s, t);
    sa.build(s);
    sa.find_lcs(s,t,lcs);
    out << lcs;
    return 0;
}