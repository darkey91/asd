#include <string>
#include <vector>
#include <fstream>
using namespace std;
int n;
 
void gen(int l, vector<string> &v, string s, char last) {
    if (l == n) {
        v.push_back(s);
        return;
    }
    gen(l + 1, v, s + '0', '0');
    if (last != '1')
        gen(l + 1, v, s + '1', '1');
}
int main() {
    ifstream in("vectors2.in");
    ofstream out("vectors2.out");
 
    in >> n;
    vector<string> v;
    string s = "0";
    gen(1, v, s, '0');
    s = "1";
    gen(1, v, s, '1');
    out << v.size() << endl;
    for (auto it : v) {
        out << it << endl;
    }
 
    return 0;
}
