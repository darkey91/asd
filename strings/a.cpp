#include <iostream>
#include <string>
#include <vector>

const long long P = 31;

void fill_degrees(std::vector<long long> &d) {
    d[0] = 1;

    for (size_t i = 1; i < d.size(); ++i) {
        d[i] = d[i - 1] * P;
    }
}

void fill_h(const std::string &s, std::vector<long long> &h) {
    h[0] = 0;
    h[1] = s[0];

    for (size_t i = 2; i < h.size(); ++i) {
        h[i] = h[i - 1] * P + s[i - 1];
    }
}


long long get_hash(size_t l, size_t r, const std::vector<long long> &h, const std::vector<long long> &d) {
    return  h[r + 1] - h[l] * d[r - l + 1];
}

int main() {
    std::string s;
    std::cin >> s;
    size_t m;
    std::cin >> m;
    std::vector<long long> degrees(s.size(), P), h(s.size() + 1, 0);
    fill_degrees(degrees);
    fill_h(s, h);

    for (size_t i = 0; i < m; ++i) {
        size_t l, r, le, ri;
        std::cin >> l >> r >> le >> ri;
        if (get_hash(l - 1, r - 1, h, degrees) == get_hash(le - 1, ri - 1, h, degrees))  {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }
    return 0;
}