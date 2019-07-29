#include <stdio.h>
#include <vector>

#define lol long long

static const lol MAX_NUMBER = 40000000;

int main() {
    std::vector<bool> prime(MAX_NUMBER + 1, true);

    prime[1] = true;
    prime[0] = false;

    for (lol i = 0; i <= MAX_NUMBER; ++i) {
         prime[i] = (i % 2 != 0);
    }

    for (lol i = 3ll; i <= MAX_NUMBER; i += 2) {
        if (prime[i] && i * i <= MAX_NUMBER)
            for (lol j = i * i; j <= MAX_NUMBER; j += i) {
                prime[j] = false;
            }
    }

    int n, x;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        if (!prime[x]) {
            printf("%s", "NO\n");
        } else {
            printf("%s", "YES\n");
        }
    }


    return 0;
}
