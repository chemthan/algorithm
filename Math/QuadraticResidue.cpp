#include <bits/stdc++.h>
using namespace std;

//Find x such that x * x = a [mod]
const int MAXN = 1e5 + 5;
int qn[MAXN];
int fpow(int n, int k, int p) {
    int r = 1;
    for (; k; k >>= 1) {
        if (k & 1) r = (long long) r * n % p;
        n = (long long) n * n % p;
    }
    return r;
}
int calc(int a, int mod) {
    if (fpow(a, (mod - 1) / 2, mod) != 1) return -1;
    if (mod % 4 == 3) return fpow(a, (mod + 1) / 4, mod);
    int q = mod - 1, s = 0;
    while (q % 2 == 0) {q /= 2; s++;}
    int z = 1;
    if (qn[mod]) z = qn[mod];
    else {
        while (z++) {
            if (fpow(z, (mod - 1) / 2, mod) == mod - 1)
                break;
        }
        qn[mod] = z;
    }
    int c = fpow(z, q, mod);
    int r = fpow(a, (q + 1) / 2, mod);
    int t = fpow(a, q, mod);
    int m = s;
    while (1) {
        if (t == 1) return r;
        int i = 1, tmp = t;
        while (i < m) {
            tmp = (long long) tmp * tmp % mod;
            if (tmp == 1) break;
            i++;
        }
        int b = c, x = m - i - 1;
        while (x > 0) {
            b = (long long) b * b % mod;
            x--;
        }
        r = (long long) r * b % mod;
        t = (long long) t * b % mod * b % mod;
        c = (long long) b * b % mod;
        m = i;
    }
}

int main() {
    int a = 2311, mod = 100000007;
    int k = calc(a, mod);
    if (k == -1) cout << -1 << "\n";
    else cout << (long long) k * k % mod;
    return 0;
}
