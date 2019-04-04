#include <iostream>
#include <string>
#include <vector>


int main() {
    std::string s;
    std::cin >> s;

    std::vector<size_t> z(s.size(), 0);
    size_t l = 0, r = 0;

    for (size_t i = 1; i < s.size(); ++i) {
        if (i > r) {
            size_t j = 0;
            while (i + j < s.size() && s[j] == s[i + j])
                ++j;
            l = i;
            r = i + j - 1;
            z[i] = j;
        } else {
            size_t j = std::min(r - i, z[i - l]);
            while (i + j < s.size() && s[j] == s[i + j]) {
                ++j;
            }
            z[i] = j;
        }
        if (i + z[i] > r) {
            l = i;
            r = z[i] + i;
        }
        std::cout << z[i] << " ";
    }


}