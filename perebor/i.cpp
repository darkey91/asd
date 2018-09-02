#include <fstream>
#include <vector>

using namespace std;

int mat[4][4] = {0}, r[4][4];
bool f = false;
vector<string> ans;

bool isEqual(string rrr) {
    int y = 0;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            r[i][j] = rrr[y++] - '0';
        }
    }

    int tmp[4][4] = {0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                tmp[i][j] = (tmp[i][j] + (r[i][k] * r[k][j]) % 2) % 2;
            }
            if (tmp[i][j] != mat[i][j]) {
                return false;
            }
        }
    }

    return true;
}

void gen(int l, string rrr) {
    if (l == 16) {
        if (isEqual(rrr)) {
            ans.push_back(rrr);
            f = true;
        }
        return;
    } else {
        if (!f)
            gen(l + 1, rrr + '0');
        if (!f)
            gen(l + 1, rrr + '1');

    }
}

int main() {
    std::ifstream in("sqroot.in");
    std::ofstream out("sqroot.out");

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            in >> mat[i][j];
        }
    }
    string rrr = "";
    gen(0, rrr);

    if (ans.empty()) out << "NO SOLUTION";
    else
        for (int i = 0; i < 16; ++i) {
            if (i != 0 && i % 4 == 0) out << "\n";
            out << ans[0][i] << " ";
        }

    return 0;
}