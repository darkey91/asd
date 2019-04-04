#include <fstream>
#include <vector>
#include <iostream>

const size_t ALPHASIZE = 256;
const char STOP = char(31);
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


long long get_hash(int l, int r, const std::vector<long long> &h, const std::vector<long long> &d) {
    return h[r + 1] - h[l] * d[r - l + 1];
}


int bin_search(const std::string &s, int first, int second, const std::vector<long long> &h,
               const std::vector<long long> &d) {
    int l = second, r = (int) s.size();
    if (s[first] != s[second]) return 0;
    if (r - l == 1) {
        bool tt = get_hash(second,second,h,d) == get_hash(first, first, h, d);
        return (int) tt;
    }
    while (l < r - 1) {
        int m = (l + r) >> 1;
        if (get_hash(first, first + m - second, h, d) == get_hash(second, m, h, d)) {
            l = m;
        } else {
            r = m;
        }
    }

    return l - second + 1;
}
class SuffixArray {
public:
    SuffixArray(const std::string &str) : str(str), suf_array(str.size()), n(str.size()) {
        std::vector<int> cnt(std::max(n, ALPHASIZE));

        std::vector<int> perm(n), c(n, 0);

        for (auto c : str) ++cnt[c];

        for (int i = 1; i < ALPHASIZE; i++) cnt[i] += cnt[i - 1];

        for (int i = 0; i < n; i++) perm[--cnt[str[i]]] = i;

        int classes_size = 1;
        for (int i = 1; i < n; i++) {
            if (str[perm[i]] != str[perm[i - 1]]) classes_size++;
            c[perm[i]] = classes_size - 1;
        }


        std::vector<int> next_p(n), next_c(n);
        for (int k = 0; (1 << k) < n; k++) {
            int len = 1 << k;
            for (int i = 0; i < n; i++) {
                next_p[i] = perm[i] - len;
                if (next_p[i] < 0) next_p[i] += n;
            }
            cnt.assign(classes_size, 0);

            for (int i = 0; i < n; i++) ++cnt[c[next_p[i]]];
            for (int i = 1; i < classes_size; i++) cnt[i] += cnt[i - 1];

            for (int i = n - 1; i >= 0; i--)
                perm[--cnt[c[next_p[i]]]] = next_p[i];

            classes_size = 1;
            for (int i = 1; i < n; i++) {
                int m1 = (perm[i] + len) % n;
                int m2 = (perm[i - 1] + len) % n;
                if (c[perm[i]] != c[perm[i - 1]] || c[m1] != c[m2])
                    ++classes_size;
                next_c[perm[i]] = classes_size - 1;
            }
            c = next_c;
        }

        for (int i = 0; i < n - 1; i++)
            suf_array[i] = perm[i + 1];
        this->str.pop_back();

    }

    void lcp(std::ofstream &out, const std::vector<long long> &h, const std::vector<long long> &d) {
        for (int i = 1; i < str.size(); ++i) {
            out << bin_search(str, std::min(suf_array[i - 1], suf_array[i]), std::max(suf_array[i - 1], suf_array[i]), h, d) << ' ';
        }
        out << '\n';
    }


    void print(std::ofstream &out) {
        for (int i = 0; i < suf_array.size() - 1; ++i) {
            out << suf_array[i] + 1 << ' ';
        }
        out << '\n';
    }

private:
    std::string str;
    size_t n;
    std::vector<int> suf_array;
};

int main() {
    std::string s;
    std::ifstream in("array.in");
    std::ofstream out("array.out");
    in >> s;
    s.push_back('_');
    SuffixArray sa(s);
    s.pop_back();
    sa.print(out);

    std::vector<long long> degrees(s.size(), P), h(s.size() + 1, 0);
    fill_degrees(degrees);
    fill_h(s, h);

    sa.lcp(out, h, degrees);

    return 0;
}
