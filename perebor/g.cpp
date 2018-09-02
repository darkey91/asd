#include <vector>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;
int n, r, ans;

bool hasTreeDiv(int d) {
    int divs = 0;
    if (d == 0) return true;
   
    if (d == 1 || d == 2) return false;
     int h = 0;
     while ((d & 1) == 0) {
         ++h;
         d >>= 1;
     }
     if (d == 1) return (h + 1) % 3 == 0;
     else divs = h + 1;
     for (int i = 3; i*i <= d; i += 2) {
         h = 0;
         while (d % i == 0) {
             ++h;
             d = d/i;
         }
         divs *= (h + 1);
     }
     if (d > 1) divs <<= 1;

    return  (divs % 3 == 0);
}

bool isBeautiful(const string &p) {
    int value = 0;
    for (int i = 1; i < p.length(); ++i) {
        value = (value + (((p[i - 1] - '0') * (p[i] - '0')) % r)) % r;
    }
    return hasTreeDiv(value);
}

void gen(int l, string p, int dig) {
    if (l == n) {
        if (isBeautiful(p)) {
            ++ans;
        }
        return;
    } else {
        for (int i = 1; i <= n; ++i) {
            bool y = (1 << (i - 1)) & dig;
            if (!y) {
                gen(l + 1, p + char(i + '0'), dig | (1 << (i - 1)));
            }
        }
    }
}

int main() {
    ifstream in("beautiful.in");
    ofstream out("beautiful.out");

    in >> n >> r;

    string p = "";

    gen(0, p, 0);
    out << ans;
    return 0;
}