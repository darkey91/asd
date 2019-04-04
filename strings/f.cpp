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
    std::ifstream in("search4.in");
    std::ofstream out("search4.out");

    int n;
    in >> n;

    std::vector<std::string> s;
    std::string t;

    for (int i = 0; i < n; ++i) {
        in >> t;
        s.push_back(t);
    }

    in >> t;

    suffix_automata sa;
    sa.build(t);

    for (auto &ss: s) {
        if(sa.accept(ss)) out << "YES\n";
        else out << "NO\n";
    }

    return 0;
}

/*ude <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <climits>
#include <set>

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
        cnt.emplace_back(0);
        length_number.emplace_back(std::make_pair(0,0));
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

    void countCnt() {
        sort(length_number.begin(), length_number.end(), [] (const auto &a, const auto &b) -> bool {
            return b.second < a.second;
        });

        for( auto &e: length_number) {
            if (cnt[e.first] > 0) {
                cnt[states[e.first].suf_link] += cnt[e.first];
            }
        }
    }

    void build(const std::string &str) {

        for (char s: str) {
            int current = size++;
            states.emplace_back(state(states[last].length + 1));
            length_number.emplace_back(std::make_pair(current,states[current].length));

            cnt.emplace_back(1);
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
private:
    int clone(int p, int q, char c) {
        ++size;
        cnt.emplace_back(0);
        states.emplace_back(states[q]);
        states.back().length = states[p].length + 1;
        length_number.emplace_back(std::make_pair(static_cast<int> (states.size() - 1),states.back().length));

        while (p >= 0 && states[p].tr.find(c)->second == q) {
            states[p].tr.find(c)->second = static_cast<int> (states.size() - 1);
            p = states[p].suf_link;
        }

        return static_cast<int> (states.size() - 1);
    }
    std::vector<int> cnt;
    std::vector<state> states;
    std::vector<std::pair<int, int>> length_number;
    int size = 0, last, root;
};

int main() {
    std::ifstream in("search5.in");
    std::ofstream out("search5.out");

    int n;
    in >> n;

    std::vector<std::string> s;
    std::string t;

    for (int i = 0; i < n; ++i) {
        in >> t;
        s.push_back(t);
    }

    in >> t;

    suffix_automata sa;
    sa.build(t);
    sa.countCnt();
    for (auto &ss: s) {
      out << sa.amount(ss) << std::endl;
    }

    return 0;
}
close*/