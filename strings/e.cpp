#include <vector>
#include <string>
#include <iostream>


int main() {
    std::string s;
    std::cin >> s;

    std::vector<size_t> pref(s.size(), 0);

    size_t max_s;
    for (size_t i = 1; i < s.size(); ++i) {
        max_s = pref[i - 1];
        while (max_s > 0 && s[i] != s[max_s]) max_s = pref[max_s - 1];
        if (s[i] == s[max_s]) ++max_s;
        pref[i] = max_s;
    }

   size_t ans = s.size() - pref[s.size() - 1];
    if (s.size() % ans != 0) ans = s.size();
    std::cout << ans;
    return 0;
}