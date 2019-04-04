#include <iostream>
#include <string>
#include <vector>
const char HOLE = '$';

int main() {
    std::string s, t;
    std::cin >> t >> s;
    s = t + HOLE + s;

    if (t.size() > s.size() - t.size() - 1) {
        std::cout << 0;
        return 0;
    }


    std::vector<size_t> pref(s.size(), 0);

    size_t max_s;
    for (size_t i = 1; i < s.size(); ++i) {
        max_s = pref[i - 1];
        while (max_s > 0 && s[max_s] != s[i]) {
            max_s = pref[max_s - 1];
        }

        if (s[i] == s[max_s]) ++max_s;
        pref[i] = max_s;
    }


    std::vector<size_t> ans;

    for (size_t i = 0; i < s.size(); ++i) {
        if (pref[i] == t.size()) ans.push_back(1 + i - 2 * t.size());
    }

    std::cout << ans.size() << std::endl;
    for (size_t a: ans) {
        std::cout << a << " ";
    }

}
