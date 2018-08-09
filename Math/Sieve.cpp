#include <bits/stdc++.h>
using namespace std;

namespace Sieve {
    const int maxn = 123456;
    void work(int n) {
        int k = sqrt(n) + 2;
        while (k * k > n) k--;
        static int ispr[maxn];
        static int prs[maxn];
        fill_n(ispr + 2, k - 1, 1);
        int npr = 0;
        for (int i = 2; i <= k; i++) if (ispr[i]) {
            for (int j = i * i; j <= k; j += i) {
                ispr[j] = 0;
            }
            prs[npr++] = i;
        }
        static int f[maxn];
        fill_n(f, k + 1, 0);
        for (int i = k + 1; i <= n; i += k) {
            int j = min(i + k - 1, n);
            for (int u = 0; u < npr; u++) {
                int p = prs[u];
                for (int q = (i + p - 1) / p * p; q <= j; q += p) {
                    f[q - i] = i;
                }
            }
            for (int u = i; u <= j; u++) if (f[u - i] < i) {
                //u is a prime
            }
        }
    }
}

int main() {
    Sieve::work((int) 1e9);
    cerr << "Correct\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
