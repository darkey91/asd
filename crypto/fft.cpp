#include <iostream>
#include <complex>
#include <vector>
#include <string>

#define PI 3.14159265359
#define co std::complex<double>

void fft(std::vector<co> &a, bool back) {
    size_t n = a.size();
    if (n == 1) return;

    std::vector<co> a0(n >> 1, co(0,0)), a1(n >> 1, co(0,0));
    for (size_t i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }

    fft(a0, back);
    fft(a1, back);

    double angle = 2 * PI/n * (back ? -1 : 1);
    co e(1,0), en(cos(angle), sin(angle));
    for (int i = 0; i < (n >> 1); ++i) {
        a[i] = a0[i] + a1[i] * e;
        a[i + (n >> 1)] = a0[i] - a1[i] * e;
        if (back) {
            a[i] /= 2;
            a[i+(n >> 1)] /=2;
        }
        e *= en;
    }

}

int main() {
    std::string f, s;
    std::cin >> f >> s;
    bool neg_f = false, neg_s = false;

    if (f[0] == '-') {
        neg_f = true;
    }
    if (s[0] == '-')    {
        neg_s = true;
    }

    size_t size = 1;
    size_t end = std::max(f.size(), s.size());
    while (size < end) {
        size <<= 1;
    }
    size <<= 1;
    std::vector<std::complex<double>> a(size, co(0,0)), b(size, co(0,0));

    size_t k = 0;

    for (int i = f.size() - 1; i >= 0 + (neg_f ? 1 : 0); --i) {
        a[k++] = std::complex<double>(f[i] - '0');
    }
    k=0;
    for (int i = s.size() - 1; i >= 0 + (neg_s ? 1 : 0); --i) {
        b[k++] = std::complex<double>(s[i] - '0');
    }

    fft(a, false);
    fft(b, false);

    for (int i = 0; i < size; ++i) {
        a[i] *= b[i];
    }

    fft(a, true);

    std::vector<int> ans(size);

    for (size_t i = 0; i < size; ++i) {
        ans[i] = static_cast<int>(a[i].real() + 0.5);
    }

    int carry = 0;
    for (size_t i = 0; i < size; ++i) {
        ans[i] += carry;
        carry = ans[i]/10;
        ans[i] %= 10;
    }

    int  c = ans.size() - 1;
    while (c >= 0 && ans[c] == 0) --c;

    if (c < 0) {
        std::cout << 0;
        return 0;
    }

    if (neg_f ^ neg_s)
        std::cout << "-";

    for (; c >= 0; --c) std::cout << ans[c];
}
