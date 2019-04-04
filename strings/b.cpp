#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string s;
    std::cin >> s;

    std::vector<size_t> prefix(s.size(), 0);
    size_t max_suf;
    for (size_t i = 1; i < s.size(); ++i) {
        max_suf = prefix[i - 1];
        while (max_suf > 0 && s[max_suf] != s[i]) {
            max_suf = prefix[max_suf - 1];
        }

        if (s[i] == s[max_suf]) ++max_suf;
        prefix[i] = max_suf;
    }


    for(size_t p: prefix) {
        std::cout << p << " ";
    }
    return 0;
}

