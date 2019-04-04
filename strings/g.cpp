#include <fstream>
#include <vector>
#include <map>

class state {
public:
    state(int length = 0, int suf_link = 0) : length(length), suf_link(suf_link) {}

    int getLength() const {
        return length;
    }

    void setLength(int length) {
        state::length = length;
    }

    int getState(char c) {
        auto it = transitions.find(c);
        return it != transitions.end() ? it->second : -1;
    }

    void addTransition(int number, char c, int length = 0) {
        transitions.insert(std::make_pair(c, number));
    }

    std::map<char, int> &getTransitions() {
        return transitions;
    }

    int getSuf_link() const {
        return suf_link;
    }

    void setSuf_link(int suf_link) {
        state::suf_link = suf_link;
    }

    void setTransitions(const std::map<char, int> &transitions) {
        state::transitions = transitions;
    }
    std::map<char, int> transitions;

private:
    int length, suf_link;
};

class SuffixAutomata {
public:
    void init() {
        states.emplace_back(state(0, -1));
        ++size;
        root = last = 0;
    }

    void build(const std::string &s) {
        for (size_t i = 0; i < s.size(); ++i) {
            int current = size++;
            states.push_back(state(states[last].getLength() + 1));

            int p = last;
            while (p >= 0 && states[p].getState(s[i]) == -1) {
                states[p].addTransition(current, s[i]);
                p = states[p].getSuf_link();
            }

            if (p != -1) {
                int q = states[p].getState(s[i]);
                if (states[p].getLength() + 1 == states[q].getLength())
                    states[current].setSuf_link(q);
                else {
                    int cl = clone(p, q, s[i]);
                    states[q].setSuf_link(cl);
                    states[current].setSuf_link(cl);
                }
            }
            last = current;
        }
    }

    bool accept(const std::string &t) {
        int cur = root;
        for (size_t i = 0; i < t.size() && cur != -1; ++i) {
            int tmp = states[cur].getState(t[i]);
            if (tmp == -1) return false;
            cur = tmp;
        }
        return true;
    }

private:

    int clone(int p, int q, char c) {
        int newState = size++;
        states.push_back(state(states[p].getLength() + 1, states[q].getSuf_link()));
        states[newState].setTransitions(states[q].getTransitions());
        while (p >= 0 && states[p].getState(c) == q) {
            states[p].transitions.find(c)->second = newState;
            p = states[p].getSuf_link();
        }
        return newState;
    }

    std::vector<state> states;
    int last = 0, root = 0, size = 0;
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

    SuffixAutomata sa;
    sa.init();
    sa.build(t);

    for (auto &ss: s) {
        if(sa.accept(ss)) out << "YES\n";
        else out << "NO\n";
    }

}